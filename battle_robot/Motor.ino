void fd(int speed){
  motor(1,speed);
  motor(2,speed);
}
void bd(int speed){
  motor(1,-speed);
  motor(2,-speed);
}
void ld(int speed){
  motor(1,-speed);
  motor(2,speed);
}
void rd(int speed){
  motor(1,speed);
  motor(2,-speed);
}
void br(){
  motor(1,0);
  motor(2,0);
}
void motorst(int spl,int spr){
  if (spl > 100){spl=100;}
  if (spr > 100){spr=100;}
  if (spl < -100){spl=-100;}
  if (spr < -100){spr=-100;}
  motor(1,spl);
  motor(2,spr);
}