#include "glut.h"	// GLUT Library (for graphics and user interaction)

void drawMaze()
{ 
	for (int i=0; i<rows; i++)
      for (int j=0; j<columns; j++)
	  {	
		  glBegin(GL_QUADS);
			  if (mazeArray[i][j] == 0)
				  glColor3f(1.0,1.0,1.0);
			  else
				  glColor3f(0.3,0.3,0.3);
			  glVertex2i(j,i);
			  glVertex2i(j,i+1);
			  glVertex2i(j+1,i+1);
			  glVertex2i(j+1,i);
		  glEnd();
		  glBegin(GL_LINE_LOOP);
			  glColor3f(0.6,0.6,0.6);
			  glVertex2i(j,i);
			  glVertex2i(j,i+1);
			  glVertex2i(j+1,i+1);
			  glVertex2i(j+1,i);
		  glEnd();
	  } 
}

void drawPath()
{
	glLineWidth(3);
	glColor3f(0.0, 0.8, 0.0);
	if (!solution.empty())
	{
		glBegin(GL_LINE_STRIP);

		list<position>::iterator itr = solution.begin();
		position p = *itr;
		glVertex2f(p.col + 0.5, p.row + 0.5);

		while (itr != solution.end())
		{
			p = *itr;
			glVertex2f(p.col + 0.5, p.row + 0.5);
			++itr;
		}
		glEnd();
	}
	glBegin(GL_LINES);
	glVertex2f(0 - 0.5, 1 + 0.5);
	glVertex2f(0 + 0.5, 1 + 0.5);

	glVertex2f(columns - 1 + 0.5, rows - 2 + 0.5);
	glVertex2f(columns + 0.5, rows - 2 + 0.5);
	glEnd();

	glLineWidth(1);
	glFlush();
}

void display()
{	
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	drawMaze();
	drawPath();
	glFlush();
}

void start_graphics_loop()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(5,5);
	glutCreateWindow("Maze Solver");
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1,columns+1,rows+1,-1);
	glutDisplayFunc(display);	
	glutMainLoop();
}