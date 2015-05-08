/*
 * GKOM Lab. 3: OpenGL
 *
 * Program stanowi zaadaptowana wersje przykladu accnot.c.
 */

#include <windows.h>
#include <GL/gl.h>
#include "GL/glut.h"

void init()
{
    GLfloat mat_ambient[]    = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat mat_specular[]   = { 1.0, 1.0,  1.0, 1.0 };
    GLfloat light_position[] = { 0.0, 0.0, 10.0, 1.0 };
    GLfloat lm_ambient[]     = { 0.2, 0.2,  0.2, 1.0 };

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient );
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
    glMaterialf( GL_FRONT, GL_SHININESS, 50.0 );
    glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lm_ambient );
    
    glShadeModel( GL_SMOOTH);

    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );

    glDepthFunc( GL_LESS );
    glEnable( GL_DEPTH_TEST );
	glEnable(GL_NORMALIZE);
	
}

void displayObjects(int frame_nr)
{
    GLfloat torus_diffuse[]  = { 0.7, 0.7, 0.0, 1.0 };
    GLfloat cube_diffuse[]   = { 0.0, 0.7, 0.7, 1.0 };
    GLfloat sphere_diffuse[] = { 0.7, 0.0, 0.7, 1.0 };
    GLfloat octa_diffuse[]   = { 0.7, 0.4, 0.4, 1.0 };

    glPushMatrix();
		
       //glRotatef( 30.0, 1.0, 0.0, 0.0 );
	   

	   glPushMatrix();

	   glRotatef(frame_nr, 0.0, 1.0, 0.0);
          glPushMatrix();
			
             glTranslatef( -0.80, 0.35, 0.0 ); 
             glRotatef( 100.0, 1.0, 0.0, 0.0 );
			 glRotatef(1.0*frame_nr, 1.0, 0.0, 0.0);
			 glScalef(0.5,0.5,0.5);
             glMaterialfv( GL_FRONT, GL_DIFFUSE, torus_diffuse );
             glutSolidTorus( 0.275, 0.85, 40, 30 );
          glPopMatrix();

		  glPushMatrix();
		  glTranslatef(0.75, 0.60, 0.0);
		  glRotatef(30.0, 1.0, 0.0, 0.0);
		  glMaterialfv(GL_FRONT, GL_DIFFUSE, sphere_diffuse);
		  glutSolidSphere(0.5*1.0, 30, 50);
		  glPopMatrix();
         
		 glPopMatrix();
		 glPushMatrix();
			//glRotatef(-frame_nr, 0.0, 1.0, 0.0);
		
        
		 glPushMatrix();
		 glTranslatef(-0.75, -0.50, 0.0);
		 glRotatef(45.0, 0.0, 0.0, 1.0);
		 glRotatef(45.0, 1.0, 0.0, 0.0);
		 glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_diffuse);
		 glutSolidCube(0.5*1.5);
		 glPopMatrix();

         glPushMatrix();
            glTranslatef( 0.70, -0.90, 0.25 ); 
            glMaterialfv( GL_FRONT, GL_DIFFUSE, octa_diffuse );
	        glutSolidTeapot( 0.5*1.0 );
         glPopMatrix();
		 glPopMatrix();

   glPopMatrix();	 
}

void display()
{
	static int frame_no = 0;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if (frame_no < 360) frame_no++;
	else frame_no = 0;
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glRotatef(frame_no, 1.0, 0.0, 0.0);
	glMatrixMode(GL_MODELVIEW);


    displayObjects(frame_no);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

    glFlush();
	glutSwapBuffers();

}

void reshape(GLsizei w, GLsizei h)
{
    if( h > 0 && w > 0 ) {
      glViewport( 0, 0, w, h );
      glMatrixMode( GL_PROJECTION );
      glLoadIdentity();
      if( w <= h ) {
         glFrustum( -1.5, 1.5, -1.5*h/w, 1.5*h/w, 1.0, 10.0 );
      }
      else {
		  glFrustum(-1.5*w / h, 1.5*w / h, -1.5, 1.5, 1.0, 10.0);
      }
	  glTranslatef(0.0, 0.0, -2.5);
      glMatrixMode( GL_MODELVIEW );
    }
}

int main(int argc, char** argv)
{
   glutInit( &argc, argv );

   glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );

   glutInitWindowPosition( 0, 0 );
   glutInitWindowSize( 1250, 800 );

   glutCreateWindow( "GPOB: OpenGL" );

   glutDisplayFunc( display );
   glutReshapeFunc( reshape );
   glutIdleFunc(display);


   init();

   glutMainLoop();

   return 0;
}
