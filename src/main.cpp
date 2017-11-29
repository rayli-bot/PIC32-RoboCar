
#include <p32mx250f128d.h>
#include "Decode.h"
#include "queue.h"
#include "state.h"
#include "compute.h"
///////////////////////////////// USB STUFF

extern "C" { // functions provided by cdc stack

void USBDeviceInit(void);
void USBDeviceTasks(void);
void CDCDeviceTasks(void);
bool USBCDCTxREADY(void);
void putsUSBUSART(char *data);	// including trailing zero
void putUSBUSART(char *data, unsigned char length);

} //extern "C"


int send=0;
static class RingBuffer {
public:
	RingBuffer(void) { read = write = 0; }
	char get(void) {
		char c = buffer[read];
		if (read == SIZE-1) read = 0;
		else read++;
		return c;
	}
	void save(char c) {
		buffer[write] = c;
		if (write == SIZE-1) write = 0;
		else write++;
	}
	int empty(void) { return read == write; }
private:
	enum {SIZE=128};		// an alternative to #define
	char buffer[SIZE];
	int read, write;
} tx;

static class ReadBuffer : public RingBuffer {
public:
	ReadBuffer(void) { free();}
	void save(char c) {
		RingBuffer::save(c);		// send to cdc (buffered) as usual
		if (!hold)					// strip UDP message into buffer
			switch (ipd) {
			case IPD:				// phase: read length
				if (c == ':') ipd = len ? -1 : 0;
				else {
					int i = c - '0';
					if (i > 9) ipd = 0;
					else len = len * 10 + i;
				}
				break;
			case -1:				// phase: save message
				buffer[index++] = c;
				if (!--len) {
					buffer[index] = 0;
					hold = true;	// message is ready for processing
				}
				break;
			default:				// phase: look for header "IPD,"
				ipd = ipd << 8 | c;
			}
	}
	char *getString(void) { return hold ? buffer : 0; }
	void free(void) { ipd = len = index = 0; hold = false; }
private:
	enum {SIZE=100, IPD='I'<<24|'P'<<16|'D'<<8|','};
	int index, ipd, len;
	char buffer[SIZE];
	bool hold;
} rx;


extern "C"	// function required by cdc stack
{

void CDCRxChars(char *c, int length) {		// you got a message from cdc
	for (int i = 0; i < length; i++) {
		if (c[i] != '\n') {					// skip linefeed
			tx.save(c[i]);
			if (c[i] == '\r') tx.save('\n');// add linefeed after carriage return
		}
	}
	IEC1bits.U2TXIE = 1;
}

void CDCTxReadyNotify(void) {				// you may send message to cdc
	static char buffer[64];
	unsigned char len = 0;
	while (!rx.empty()) buffer[len++] = rx.get();
	//if (len) putUSBUSART(buffer, len);
}

} //extern "C"

namespace
{

void USBTasks(void) {
	USBDeviceTasks();
	U1OTGIR = 0xFF;
	IFS1bits.USBIF = 0;
	CDCDeviceTasks();
}

void int2char(int u, char *c) {		// unsigned short to ASCII string
	int i, t, r;
	for (i = 0; i < 5; i++) c[i] = '0';	// clear string
	if(u<0) { c[0]='-'; u=-u;}
	else c[0]='+';
	c[i] = '0';							// default zero
	while (u) {							// u must be unsigned short
		t = u / 10;
		r = u - t * 10;
		u = t;
		c[i--] = '0' + r;
	}
}

char string2[]= "RayL: 0000    0000    0000    0000    0000    0000    0000    0000      \r\n";

void print2(){
	int2char(getX(0), &string2[6]);
	int2char(getY(0), &string2[14]);
	int2char(getX(1),&string2[22]);
	int2char(getY(1),&string2[30]);
	int2char(getX(3),&string2[38]);
	int2char(getY(3),&string2[46]);
	int2char(getX(4),&string2[54]);
	int2char(getY(4),&string2[62]);
	putsUSBUSART(string2);
}

} // anonymous namespace for privacy
int main(void) {
	char *s, buffer[128];
	USBDeviceInit();
	initStatus();
	while (1) {
			USBTasks();
				s = rx.getString();
				if (s) {
					unsigned char len = 0;
					while ((buffer[len] = s[len])) len++;
					buffer[len++]='\r';
					//received!!
					Raw2Locate(buffer);
					print2();
					rx.free();
				}
		}
}


extern "C" void __attribute__ ((interrupt)) u2ISR(void) {
	while (U2STAbits.URXDA) rx.save(U2RXREG);
	IFS1bits.U2RXIF = 0;
	if (IEC1bits.U2TXIE) {
		while (!U2STAbits.UTXBF) {
			if (tx.empty()) { IEC1bits.U2TXIE = 0; break; }
			else U2TXREG = tx.get();
		}
		IFS1bits.U2TXIF = 0;
	}
}
