#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdio>
#include <memory.h>
#include <GL/glut.h>
#include "EvacuationTimeViewer.h"
using namespace std;

//--- Select Values
const unsigned int ME              =  33414; // All Grids Number
const double       DX              =    2.0; // Grid Size
const double       COLOR_RANGE_LOW =    0.0; // Color Range Low
const double       COLOR_RANGE_TOP = 300.0; // Color Range Top
const double       MOVING_SPEED    =    0.5; // Moving Speed (m/s)

//--- Variables
double xMax, yMax;
double mex[ME], mey[ME+1];
float  t_evac[ME+1];
float  m_vertex[ME+1][4][2];
float  m_color [ME+1][4][3];
int    w_mode  [ME+1][4];
int    mr[ME+1], mb[ME+1], ml[ME+1], mu[ME+1];

//-------------------
// Initialize
//-------------------
void initialize(int argc, char *argv[])
{
	string str;
	int i, j, wl, wb, id, rr, bb, ll, uu;

	//--- Load Grid File
	ifstream ifs1("../in/Mesh.csv");

	// Load Headers
	getline(ifs1, str, '\n');
	getline(ifs1, str, '\n');
	getline(ifs1, str, '\n');

	// Load Grid Data
	xMax = yMax = 0.0;
	float cpt0[3] = { 1.0, 1.0, 1.0 };
	float cpt1[3] = { 0.0, 0.0, 0.0 };
	while (ifs1 >> id >> rr >> bb >> ll >> uu >> i >> j >> str >> wl >> wb >> str >> str >> str)
	{
		// Wall Mode
		w_mode[id][0] = 0;
		w_mode[id][1] = 0;
		w_mode[id][2] = 0;
		w_mode[id][3] = 0;

		mr[id] = rr;
		mb[id] = bb;
		ml[id] = ll;
		mu[id] = uu;

		if (mu[id] > ME)            w_mode[id][0] = 1;
		if (ml[id] > ME || wl != 0) w_mode[id][1] = 1;
		if (mb[id] > ME || wb != 0) w_mode[id][2] = 1;
		if (mr[id] > ME)            w_mode[id][3] = 1;

		// Ragion Range
		mex[id] = (double)i * DX;
		mey[id] = (double)j * DX;
		if (xMax < mex[id]) xMax = mex[id];
		if (yMax < mey[id]) yMax = mey[id];
	}

	//--- Set Grid Vertex
	for (id = 1; id <= ME; ++id){
		m_vertex[id][0][0] = mex[id]     ; m_vertex[id][0][1] = mey[id];
		m_vertex[id][1][0] = mex[id] - DX; m_vertex[id][1][1] = mey[id];
		m_vertex[id][2][0] = mex[id] - DX; m_vertex[id][2][1] = mey[id] - DX;
		m_vertex[id][3][0] = mex[id]     ; m_vertex[id][3][1] = mey[id] - DX;
	}

	//--- Calculation Evacuation Time
    for(id = 0; id <= ME; ++id) t_evac[id] = 999999999.9;

	ifstream ifs2("../in/ExitGrid.dat");

	while(ifs2 >> id){
		t_evac[id] = 0.0;
		calcEvacuationTime(id, 0.0);
	}

	//--- Set Evacuation Time Color
	float cpt[3];
	for (id = 1; id <= ME; ++id){
		cpt[0] = 1.0;
		cpt[1] = 1.0;
		cpt[2] = 1.0;
		setColor(t_evac[id], cpt);
		memcpy(m_color[id][0], cpt, sizeof(cpt));
		memcpy(m_color[id][1], cpt, sizeof(cpt));
		memcpy(m_color[id][2], cpt, sizeof(cpt));
		memcpy(m_color[id][3], cpt, sizeof(cpt));
	}
}

//-------------------
// Initialize View Port
//-------------------
void initViewPort
(int DISP_SIZE_W, int DISP_SIZE_H, int ADX, int ADY, double ALP)
{
	double xmpp, ympp, xLen, yLen, vLeft, vRight, vBottom, vTop;
	double viewPort[4][2];
	static const int VIEW_SIZE_W = DISP_SIZE_W - 10;
	static const int VIEW_SIZE_H = DISP_SIZE_H - DISP_SIZE_H / 10 - 10;

	//--- Initialize View Port
	// Calculate Length per Pixcel
	xmpp = (xMax + (10.0 * DX)) / (double)VIEW_SIZE_W;
	ympp = (yMax + (10.0 * DX)) / (double)VIEW_SIZE_H;
	if (xmpp > ympp){ ympp = xmpp; }
	else            { xmpp = ympp; }

	xLen = 0.5 * (double)DISP_SIZE_W * xmpp * ALP;
	yLen = 0.5 * (double)DISP_SIZE_H * ympp * ALP;

	// View Port Setting
	vLeft = 0.5 * xMax - xLen + (double)ADX * xmpp;
	vRight = 0.5 * xMax + xLen + (double)ADX * xmpp;
	vBottom = 0.5 * yMax - yLen + (double)ADY * ympp;
	vTop = 0.5 * yMax + yLen + (double)ADY * ympp;

	// Set View Port
	glViewport(5.0, 65.0, VIEW_SIZE_W, VIEW_SIZE_H);
	glLoadIdentity();
	gluOrtho2D(vLeft, vRight, vBottom, vTop);

	// Initialize View Port
	viewPort[0][0] = vLeft; viewPort[0][1] = vBottom;
	viewPort[1][0] = vRight; viewPort[1][1] = vBottom;
	viewPort[2][0] = vRight; viewPort[2][1] = vTop;
	viewPort[3][0] = vLeft; viewPort[3][1] = vTop;

	// Show View Port
	glColor3f(1.0, 1.0, 1.0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_DOUBLE, 0, viewPort);
	glDrawArrays(GL_POLYGON, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
}

//-------------------
// Drow Legend
//-------------------
void drowLegend
(int DISP_SIZE_W, int DISP_SIZE_H)
{
	unsigned int n, k;
	double lx0, ly0, lw0, lh0;
	double time;
	float  cpt[3];
	GLdouble vertexLegend[9][4][2];
	GLdouble colorLegend[9][4][3];

	glClearColor(0.8, 0.8, 0.8, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//--- View Port Setting
	glViewport(0.0, 0.0, DISP_SIZE_W, DISP_SIZE_H);
	glLoadIdentity();
	gluOrtho2D(0.0, (double)DISP_SIZE_W, 0.0, (double)DISP_SIZE_H);

	//--- Drow Color Legend

	// Make Legend Vertex
	lx0 = (double)DISP_SIZE_W / 2.0 - 180.0;
	ly0 = 40.0;
	lw0 = 40.0;
	lh0 = 20.0;

	for (n = 0; n < 9; ++n){
		vertexLegend[n][0][0] = lx0 + lw0*(n); vertexLegend[n][0][1] = ly0;
		vertexLegend[n][1][0] = lx0 + lw0*(n + 1); vertexLegend[n][1][1] = ly0;
		vertexLegend[n][2][0] = lx0 + lw0*(n + 1); vertexLegend[n][2][1] = ly0 + lh0;
		vertexLegend[n][3][0] = lx0 + lw0*(n); vertexLegend[n][3][1] = ly0 + lh0;
	}

	// Select Legend Color
	setColor(COLOR_RANGE_LOW, cpt);
	for (n = 0; n < 3; ++n){
		colorLegend[0][0][n] = cpt[n];
		colorLegend[0][3][n] = cpt[n];
	}

	setColor(COLOR_RANGE_TOP, cpt);
	for (n = 0; n < 3; ++n){
		colorLegend[8][1][n] = cpt[n];
		colorLegend[8][2][n] = cpt[n];
	}

	for (n = 1; n < 9; ++n){
		time = COLOR_RANGE_LOW + (COLOR_RANGE_TOP - COLOR_RANGE_LOW)*n / 9.;
		setColor(time, cpt);
		for (k = 0; k < 3; ++k){
			colorLegend[n][0][k] = cpt[k];
			colorLegend[n][3][k] = cpt[k];
			colorLegend[n - 1][1][k] = cpt[k];
			colorLegend[n - 1][2][k] = cpt[k];
		}
	}

	// Activate
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Association
	glVertexPointer(2, GL_DOUBLE, 0, vertexLegend);
	glColorPointer(3, GL_DOUBLE, 0, colorLegend);
	glDrawArrays(GL_QUADS, 0, 4 * 9);

	// Deactivate
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);


	//--- Color Legend Title
	ostringstream s1, s2;
	s1 << fixed << setprecision(0) << COLOR_RANGE_LOW / 60.0 << " min";
	glDrowChar(s1.str().c_str(), lx0 - 20.0, 20.0);

	s2 << "Over " << fixed << setprecision(0) << COLOR_RANGE_TOP / 60.0 << " min";
	glDrowChar(s2.str().c_str(), lx0 + lw0 * 9 -55.0, 20.0);

	glFlush();
}

//-------------------
// Drow Evacuation Time
//-------------------
void drowEvacuationTime(int DISP_SIZE_W, int DISP_SIZE_H)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, m_vertex);
	glColorPointer(3, GL_FLOAT, 0, m_color);
	glDrawArrays(GL_QUADS, 0, 4 * ME);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glFlush();
}

//-------------------
// Drow Wall
//-------------------
void drowWall(int DISP_SIZE_W, int DISP_SIZE_H)
{
	unsigned int id;

	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	for (id = 1; id <= ME; ++id){
		if (w_mode[id][0] == 1){
			glVertex2f(m_vertex[id][0][0], m_vertex[id][0][1]);
			glVertex2f(m_vertex[id][1][0], m_vertex[id][1][1]);
		}
		if (w_mode[id][1] == 1){
			glVertex2f(m_vertex[id][1][0], m_vertex[id][1][1]);
			glVertex2f(m_vertex[id][2][0], m_vertex[id][2][1]);
		}
		if (w_mode[id][2] == 1){
			glVertex2f(m_vertex[id][2][0], m_vertex[id][2][1]);
			glVertex2f(m_vertex[id][3][0], m_vertex[id][3][1]);
		}
		if (w_mode[id][3] == 1){
			glVertex2f(m_vertex[id][3][0], m_vertex[id][3][1]);
			glVertex2f(m_vertex[id][0][0], m_vertex[id][0][1]);
		}

	}
	glEnd();

	glFlush();
}

//-------------------
// Set Color
//-------------------
void setColor
(float time, float cpt[])
{
	unsigned int n;
	float p, grd;
	float  cr[9] = { 0, 0, 0, 90, 255, 255, 255, 255, 255 };
	float  cg[9] = { 0, 80, 240, 255, 255, 255, 170, 85, 0 };
	float  cb[9] = { 205, 255, 110, 30, 0, 0, 0, 0, 0 };
	float  lv[10] = { 0., 1. / 9., 2. / 9., 3. / 9., 4. / 9.,
		5. / 9., 6. / 9., 7. / 9., 8. / 9., 1. };

	for (n = 0; n < 9; ++n){
		cr[n] = cr[n] / 255.;
		cg[n] = cg[n] / 255.;
		cb[n] = cb[n] / 255.;
	}

	p = (time - COLOR_RANGE_LOW) / (COLOR_RANGE_TOP - COLOR_RANGE_LOW);
	if (p <  0.0) p = 0.0;
	if (p >= 1.0) p = 1.0;

	cpt[0] = cr[0];
	cpt[1] = cg[0];
	cpt[2] = cb[0];

	for (n = 0; n < 9; ++n){
		if (p <= lv[n + 1]){
			grd = (p - lv[n]) / (lv[n + 1] - lv[n]);
			cpt[0] = cr[n] + (cr[n + 1] - cr[n]) * grd;
			cpt[1] = cg[n] + (cg[n + 1] - cg[n]) * grd;
			cpt[2] = cb[n] + (cb[n + 1] - cb[n]) * grd;
			break;
		}
	}
}

//-------------------
// Drow Characters
//-------------------
void glDrowChar(const char ch[], double xp, double yp)
{
	glColor3d(0.0, 0.0, 0.0);
	glRasterPos2d(xp, yp);
	while (*ch){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *ch);
		++ch;
	}
}

//-------------------
// Calculation Evacuation Time
//-------------------
int calcEvacuationTime(int id, double tt)
{
	tt += DX / MOVING_SPEED;
	if (COLOR_RANGE_TOP * 1.5 < tt) return 0;

	// Right Direction Moving
	if(w_mode[id][3] == 0){
		if (w_mode[mr[id]][1] == 0 && t_evac[mr[id]] > tt){
			t_evac[mr[id]] = tt;
			calcEvacuationTime(mr[id], tt);
		}
	}

	// Up Direction Moving
	if(w_mode[id][0] == 0){
		if (w_mode[mu[id]][2] == 0 && t_evac[mu[id]] > tt){
			t_evac[mu[id]] = tt;
			calcEvacuationTime(mu[id], tt);
		}
	}

	// Left Direction Moving
	if(w_mode[id][1] == 0){
		if (w_mode[ml[id]][3] == 0 && t_evac[ml[id]] > tt){
			t_evac[ml[id]] = tt;
			calcEvacuationTime(ml[id], tt);
		}
	}

	// Bottom Direction Moving
	if(w_mode[id][2] == 0){
		if (w_mode[mb[id]][0] == 0 && t_evac[mb[id]] > tt){
			t_evac[mb[id]] = tt;
			calcEvacuationTime(mb[id], tt);
		}
	}

	return 0;
}