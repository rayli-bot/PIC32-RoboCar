#ifndef COMPUTE_H_
#define COMPUTE_H_


const int arctanLUT[44][3]={
{2,0,7},{6,7,15},{10,15,22},{14,22,29},{18,29,37},
{22,37,45},{26,45,54},{30,54,63},{34,63,73},{38,73,84},
{42,84,97},{46,97,112},{50,112,128},{54,128,149},{58,149,174},
{62,174,206},{66,206,248},{70,248,308},{74,308,402},{78,402,568},
{82,568,952},{86,952,2864},{-2,-7,0},{-6,-15,-7},{-10,-22,-15},
{-14,-29,-22},{-18,-37,-29},{-22,-45,-37},{-26,-54,-45},{-30,-63,-54},
{-34,-73,-63},{-38,-84,-73},{-42,-97,-84},{-46,-112,-97},{-50,-128,-112},
{-54,-149,-128},{-58,-174,-149},{-62,-206,-174},{-66,-248,-206},{-70,-308,-248},
{-74,-402,-308},{-78,-568,-402},{-82,-952,-568},{-86,-2864,-952}
};

const int rootLUT[100]={0,1,1,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10};

int Angle(int,int,int,int);
int Root(int);
int Distance(int,int,int,int);
int ShootError(int,int,int);
int overhead(int);
int PointError(int,int);
int CheckDistance(int,int,int,int,int);

#endif /* COMPUTE_H_ */