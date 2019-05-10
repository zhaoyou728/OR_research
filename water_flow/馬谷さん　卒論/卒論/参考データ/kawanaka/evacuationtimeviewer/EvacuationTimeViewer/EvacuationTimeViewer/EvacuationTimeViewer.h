#ifndef _INC_VIEWER
#define _INC_VIEWER
//--- Functions
extern void initialize(int argc, char *argv[]);
extern void drowLegend(int DISP_SIZE_W, int DISP_SIZE_H);
extern void drowEvacuationTime(int DISP_SIZE_W, int DISP_SIZE_H);
extern void drowWall(int DISP_SIZE_W, int DISP_SIZE_H);
extern void setColor(float time, float cpt[]);
extern void glDrowChar(const char ch[], double xp, double yp);
extern void initViewPort(int DISP_SIZE_W, int DISP_SIZE_H, int ADX, int ADY, double ALP);
extern int  calcEvacuationTime(int id, double tt);

#endif