#define DIVSP(a,b) ((a)/(b))
#define CV_OBJECT_WINOVERLAP_NORM_VALUE (100)

static int32_t getWindowOverlapArea
(
    uint16_t x1, uint16_t y1, uint16_t width1, uint16_t height1,
    uint16_t x2, uint16_t y2, uint16_t width2, uint16_t height2
)
{

  int32_t rect1x[4];
  int32_t rect2x[4];
  int32_t srect[4];
  rect1x[0] = x1; rect1x[1] = y1; rect1x[2] = x1+width1; rect1x[3] = y1+height1;
  rect2x[0] = x2; rect2x[1] = y2; rect2x[2] = x2+width2; rect2x[3] = y2+height2;
  srect[0]  = MAX(rect1x[0], rect2x[0]);
  srect[1]  = MAX(rect1x[1], rect2x[1]);
  srect[2]  = MIN(rect1x[2], rect2x[2]);
  srect[3]  = MIN(rect1x[3], rect2x[3]);


  int32_t area = 0;
  if ((srect[2] >  srect[0]) && (srect[3] > srect[1]))
  {
    area =(srect[2] -  srect[0]) * (srect[3] - srect[1]);
  }
  return area;
}

int32_t getWindowOverlapScore(sRect *rect1, sRect *rect2, uint8_t minDen)
{
  int32_t width1;
  int32_t height1;
  int32_t width2;
  int32_t height2;
  uint16_t x1, x2;
  uint16_t y1, y2;
  int32_t ov;
  int32_t a1;
  int32_t a2;
  int32_t den;
  int32_t rnd;
  int32_t score;

  x1 = (uint16_t)rect1->point.x;
  x2 = (uint16_t)rect2->point.x;

  y1 = (uint16_t)rect1->point.y;
  y2 = (uint16_t)rect2->point.y;

  width1  = (uint16_t)rect1->width;
  height1 = (uint16_t)rect1->height;
  width2  = (uint16_t)rect2->width;
  height2 = (uint16_t)rect2->height;

  ov    = getWindowOverlapArea(x1,y1,width1,height1,x2,y2,width2,height2);
  a1    = width1*height1;
  a2    = width2*height2;
  den   = minDen ? MIN(a1,a2):(a1 + a2 - ov); // minDen=0 ,den = (a1 + a2 -ov)
  rnd   = 0;
  score = (int32_t)(den > 0)? DIVSP((ov * CV_OBJECT_WINOVERLAP_NORM_VALUE + rnd) , den) : 0;  

  return score;
}
