/*
 * Taak : Complexe Geometrie (Zeepkist)
 *
 * Pieter-Jan Steeman
 * r06286772
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>

#define esc 27

GLubyte projection = 'O';
GLdouble scale = 1;

GLdouble Xmin = -5, Xmax = 10, Ymin = -3, Ymax = 12;
GLdouble Near = 1.0, Far = 1000.0;

GLdouble Xlens = -50.0, Ylens = 6.0, Zlens = -1.0;
GLdouble Xref = 0.0, Yref = 0.0, Zref = 0.0;
GLdouble Xvw = 0.0, Yvw = 1.0, Zvw = 0.0;

GLfloat wit[] = {1.0,1.0,1.0,1.0};
GLfloat groen[] = {0.0,1.0,0.0,1.0};
GLfloat blauw[] = {0.0,0.0,1.0,1.0};
GLfloat rood[] = {1.0,0.0,0.0,1.0};
GLfloat geel[] = {1.0,1.0,0.0,1.0};
GLfloat zwart[] = {0.0,0.0,0.0,1.0};

GLfloat licht0[] = {10.0, 10.0, 5.0, 0.0};
GLfloat licht1[] = {-10.0, 10.0, 10.0, 0.0};
GLfloat licht2[] = {5.0, 10.0, 10.0, 0.0};
GLfloat licht3[] = {0.0, 7.5, 0.0, 1.0};

GLfloat grijs_a[] = {0.22,0.22,0.22,1.0};      //grijs
GLfloat grijs_d[] = {0.33,0.33,0.33,1.0};
GLfloat grijs_s[] = {0.11,0.11,0.11,1.0};

GLfloat wit_a[] = {0.66,0.66,0.66,1.0};      //witachtig
GLfloat wit_d[] = {0.77,0.77,0.77,1.0};
GLfloat wit_s[] = {0.55,0.55,0.55,1.0};

GLfloat chrome_a[] = {0.46,0.58,0.35,1.0};       //chrome
GLfloat chrome_d[] = {0.23,0.29,0.17,1.0};
GLfloat chrome_s[] = {0.69,0.87,0.52,1.0};

GLfloat brons_a[] = {0.21,0.13,0.10,1.0};       //brons
GLfloat brons_d[] = {0.39,0.27,0.17,1.0};
GLfloat brons_s[] = {0.71,0.43,0.18,1.0};

GLfloat geel_a[] = {0.65,0.55,0.15,1.0};      //geel
GLfloat geel_d[] = {0.75,0.45,0.15,1.0};
GLfloat geel_s[] = {0.85,0.35,0.15,1.0};

GLfloat lila_a[] = {0.45,0.15,0.75,1.0};      //lila
GLfloat lila_d[] = {0.55,0.15,0.65,1.0};
GLfloat lila_s[] = {0.35,0.15,0.85,1.0};

GLint slices = 32;
GLint stacks = 32;

GLint shading = 0;      /* 0 = FLAT   1 = SMOOTH */

GLfloat spotAngle = 30.0;
GLfloat spotExp = 20.0;
GLfloat spotHeight = 0.0;
GLfloat boogPlaats[] = {15.0, 7.5, 3.5, 1.0};

GLdouble shininess = 0.0;
GLfloat hoek = 0.0;
GLfloat rijden = 0.0;

GLfloat afgrond = 200.0;
GLfloat startpunt = -50.0;

GLint wireFrame = 0;    /* 0 = UIT   1 = AAN*/
GLint axis = 1;         /* 0 = UIT   1 = AAN*/
GLint checkPoints = 0;  /* 0 = UIT   1 = AAN*/
GLint more = 0;         /* 0 = UIT   1 = AAN*/
GLint seeThrough = 0;   /* 0 = UIT   1 = AAN*/
GLint jpegTexture = 0;  /* 0 = UIT   1 = AAN*/
GLint wielDraai = 0;    /* 0 = UIT   1 = AAN*/
GLint zeepRij = 0;      /* 0 = UIT   1 = AAN*/
GLint fog = 0;          /* 0 = UIT   1 = AAN*/
GLint fogExp = 0;       /* 0 = UIT   1 = AAN*/
GLint inzitter = 0;
GLint persoon = 1;

GLint carrText = 1;
GLint ondText = 1;
GLint boogText = 1;

/*          Lichten Functie
 *
 */
void lichten(void)
{
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, zwart);      // eerst alles op zwart zetten zodat er niets perongeluk al een kleur heeft
    glLightfv(GL_LIGHT0,GL_AMBIENT,zwart);
    glLightfv(GL_LIGHT1,GL_AMBIENT,zwart);
    glLightfv(GL_LIGHT2,GL_AMBIENT,zwart);
    glLightfv(GL_LIGHT3,GL_AMBIENT,zwart);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,zwart);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,zwart);
    glLightfv(GL_LIGHT2,GL_DIFFUSE,zwart);
    glLightfv(GL_LIGHT3,GL_DIFFUSE,zwart);
    glLightfv(GL_LIGHT0,GL_SPECULAR,zwart);
    glLightfv(GL_LIGHT1,GL_SPECULAR,zwart);
    glLightfv(GL_LIGHT2,GL_SPECULAR,zwart);
    glLightfv(GL_LIGHT3,GL_SPECULAR,zwart);

    glLightfv(GL_LIGHT0,GL_AMBIENT,wit);            // hier worden de waarden voor de lichten echt ingesteld
    glLightfv(GL_LIGHT1,GL_DIFFUSE,groen);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,blauw);
    glLightfv(GL_LIGHT2,GL_SPECULAR,rood);
    glLightfv(GL_LIGHT3,GL_AMBIENT,geel);
    glLightfv(GL_LIGHT3,GL_DIFFUSE,geel);
    glLightfv(GL_LIGHT3,GL_SPECULAR,geel);
}

/*          Toetsen Functie
 * x/X - y/Y - z/Z verplatsen oog
 * a/A - b/B - c/C - d/D aan/uitschakelen lichtbronnen
 * s/S keuze FLAT en SMOOTH shading
 * v/V verkleinen/vergroten spothoek
 * w/W aanpassen spot expontent (stappen van 5 met initiële waarde = 20)
 * h/H aanpassen hoogte van de spot
 * e/E aanpassen shininess (stappen van 5 met initiële waarde = 10)
 * l zichtbaarheid draadmodellen
 * j assen
 * k controlepunten van de oppervlaken
 * n meerdere zeepkisten
 * f doorzichtig maken van carrosserie
 * t jpeg textuur van de carroserrie en de boog
 * g draaien van de wielen
 * G bewegen van de zeepkist
 * m mist
 * M exponentiëel effect mist
 * i schakeld de inzitter aan/uit
 * 1 : Mr. Crauwles
 * 2 : Mvr. Philips
 * 3 : Mr. Meel
 */
void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'x' : Xlens++;  break;     case 'X' : Xlens--;  break;
		case 'y' : Ylens++;  break;     case 'Y' : Ylens--;  break;
		case 'z' : Zlens++;  break;     case 'Z' : Zlens--;  break;

		case 'a' : glEnable(GL_LIGHT0);    break;      case 'A' : glDisable(GL_LIGHT0);    break;
		case 'b' : glEnable(GL_LIGHT1);    break;      case 'B' : glDisable(GL_LIGHT1);    break;
		case 'c' : glEnable(GL_LIGHT2);    break;      case 'C' : glDisable(GL_LIGHT2);    break;
		case 'd' : glEnable(GL_LIGHT3);    break;      case 'D' : glDisable(GL_LIGHT3);    break;

		case 's' : shading = 0;     break;      case 'S' : shading = 1;     break;

		case 'v' : spotAngle++;     break;      case 'V' : spotAngle--;     break;
		case 'w' : spotExp++;       break;      case 'W' : spotExp--;       break;
		case 'h' : spotHeight++;    break;      case 'H' : spotHeight--;    break;

		case 'e' : shininess++;     break;      case 'E' : shininess--;     break;

        case 'l' : wireFrame = !wireFrame;      break;
		case 'j' : axis = !axis;                break;
		case 'k' : checkPoints = !checkPoints;  break;
		case 'n' : more = !more;                break;
		case 'f' : seeThrough = !seeThrough;    break;
		case 't' : jpegTexture = !jpegTexture;  break;
		case 'g' : wielDraai = !wielDraai;      break;
		case 'G' : zeepRij = !zeepRij;          break;
		case 'm' : fog = !fog;                  break;
		case 'M' : fogExp = !fogExp;            break;
		case 'i' : inzitter = !inzitter;        break;

		case '1' : persoon = 1;     break;
		case '2' : persoon = 2;     break;
		case '3' : persoon = 3;     break;

		case 27 :
        case 'q':
            exit(0);
            break;
    }
    printf("    %5.1f       %5.1f       %5.1f \n", Xlens, Ylens, Zlens );

    glutPostRedisplay();
}

/*          Herschaal Functie
 * raam : O(rtogonaal)  S(ymetrisch perspectied   A(lgemeen) perspectief
 */
void resize(GLint newWidth, GLint newHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switch (projection)
    {
        case 'S':
            gluPerspective(60.0, 1.0, Near, Far);
            break;
        case 'A':
            glFrustum(Xmin, Xmax, Ymin, Ymax, Near, Far);
            break;
        default:
        case 'O':
            glOrtho(Xmin, Xmax, Ymin, Ymax, Near, Far);
            break;
    }
    glViewport(0, 0, newWidth, newHeight);
    if (newWidth < newHeight * scale)
    {
        glViewport(0,0, newWidth*scale, newWidth);
    }
    else
    {
        glViewport(0,0, newHeight*scale, newHeight);
    }
}

/*          Texture Mapping
 *
 */
void textureMenu(GLint keuze)
{
    switch(keuze)
    {
        case 1: carrText = 1;
            break;
        case 2: carrText = 0;
            break;
        case 3: ondText = 1;
            break;
        case 4: ondText = 0;
            break;
        case 5: boogText = 1;
            break;
        case 6: boogText = 0;
            break;
    }
    glutPostRedisplay();
}

/*          As functie
 * Helpt bij het tekenen van de assen
 * axisChar geeft de asnaam aan, axisLength bepaald de lengte van de getekende as
 */
void axisFunc(GLubyte axisChar, GLdouble axisLength)
{
    glLineWidth(1.5);
    if(axisChar == 'x')
    {
        glColor3f(0.0, 0.1, 0.8);
    }
    else if (axisChar == 'y')
    {
        glColor3f(0.0, 0.8, 0.1);
    }
    else
    {
        glColor3f(0.8, 0.1, 0.0);
    }

    glBegin(GL_LINES);
		glVertex3d(0.0, 0.0, 0.0);
		glVertex3d(0.0, 0.0, axisLength);
	glEnd();
}

/*          Aankomst functie
 *  tekent de aankomst en geeft hem zijn materiaaleigenschappen
 */
void aankomst(void)
{
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    if(wireFrame)
        gluQuadricDrawStyle(quadratic, GLU_SILHOUETTE);
    else
        gluQuadricDrawStyle(quadratic, GLU_FILL);

    if(boogText)
    {
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,geel_a);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,geel_d);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,geel_s);
    }
    else
    {
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,lila_a);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,lila_d);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,lila_s);
    }

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();                         //blauwe cilinder
    glTranslated(50, 0, -3);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(quadratic, 1, 1, 7.5, slices, stacks);
    gluDisk(quadratic, 0, 1.0, slices, stacks);
    glTranslated(0.0, 0.0, 0.5);
    gluDisk(quadratic, 0, 1.0, slices, stacks);
	glPopMatrix();

    glPushMatrix();                         //blauwe cilinder
    glTranslated(50, 0, 10);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(quadratic, 1, 1, 7.5, slices, stacks);
    gluDisk(quadratic, 0, 1.0, slices, stacks);
    glTranslated(0.0, 0.0, 0.5);
    gluDisk(quadratic, 0, 1.0, slices, stacks);
	glPopMatrix();
}

/*          Zeepkist Functie
 *  Deze tekent de zeekpist en geeft hem ook zijn materiaaleigenschappen
 */

void zeepkist(void)
{
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    GLUquadricObj *shirt;
    shirt = gluNewQuadric();

    GLUquadricObj *hoofd;
    hoofd = gluNewQuadric();

    if(wireFrame)
        gluQuadricDrawStyle(quadratic, GLU_SILHOUETTE);
    else
        gluQuadricDrawStyle(quadratic, GLU_FILL);

    if(carrText)
    {
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,grijs_a);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,grijs_d);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,grijs_s);

    }
    else
    {
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,wit_a);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,wit_d);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,wit_s);
    }

    if(ondText)
    {
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,chrome_a);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,chrome_d);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,chrome_s);
    }
    else
    {
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,brons_a);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,brons_d);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,brons_s);
    }
	//glColor3f(1.0, 1.0, 0.0);               //gele deel achter onderstel
    glPushMatrix();
    glTranslated(4.5+rijden, 1.5, 3.0);
    glScaled(17.0, 1.0, 1.0);
    if(wireFrame)
        glutWireCube(0.5);
    else
        glutSolidCube(0.5);
	glPopMatrix();

	//glColor3f(1.0, 1.0, 0.0);               //gele deel voor onderstel
    glPushMatrix();
    glTranslated(4.5+rijden, 1.5, 4.0);
    glScaled(17.0, 1.0, 1.0);
    if(wireFrame)
        glutWireCube(0.5);
    else
        glutSolidCube(0.5);	glPopMatrix();

	//glColor3f(0.0, 1.0, 1.0);               //cyaan deel onderstel
    glPushMatrix();
    glTranslated(0+rijden, 1.5, 3.5);
    glScaled(1.0, 1.0, 12.0);
    if(wireFrame)
        glutWireCube(0.5);
    else
        glutSolidCube(0.5);	glPopMatrix();

    glDisable(GL_LIGHTING);                 //om de banden en het zitje steeds dezelfde kleur te doen hebben

	glColor3f(0.3, 0.3, 0.3);               //linkerachter wiel
	glPushMatrix();
    glTranslated(0+rijden, 1.5, 0.0);
    glRotatef(hoek, 0.0, 0.0, 1.0);
    gluCylinder(quadratic, 1.5, 1.5, 0.5, slices, stacks);
    gluDisk(quadratic, 0, 1.5, slices, stacks);
    glTranslated(0.0, 0.0, 0.5);
    gluDisk(quadratic, 0, 1.5, slices, stacks);
	glPopMatrix();

	glPushMatrix();                         //rechterachter wiel
    glTranslated(0+rijden, 1.5, 6.5);
    glRotatef(hoek, 0.0, 0.0, 1.0);
    gluCylinder(quadratic, 1.5, 1.5, 0.5, slices, stacks);
    gluDisk(quadratic, 0, 1.5, slices, stacks);
    glTranslated(0.0, 0.0, 0.5);
    gluDisk(quadratic, 0, 1.5, slices, stacks);
	glPopMatrix();

	glPushMatrix();                         //voor wiel
    glTranslated(8.75+rijden, 1.5, 3.25);
    glRotatef(hoek, 0.0, 0.0, 1.0);
    gluCylinder(quadratic, 1.5, 1.5, 0.5, slices, stacks);
    gluDisk(quadratic, 0, 1.5, slices, stacks);
    glTranslated(0.0, 0.0, 0.5);
    gluDisk(quadratic, 0, 1.5, slices, stacks);
	glPopMatrix();

	GLdouble zit[4] = { 0.0, 1, 0.0, -1.75}; //waar men moet clippen

	glClipPlane(GL_CLIP_PLANE0, zit);
    glEnable(GL_CLIP_PLANE0);

	glColor3f(1.0, 0.3, 0.4);               //zitje
	glPushMatrix();
    glTranslated(1.25+rijden, 2.25, 3.5);
    glRotatef(90, 1, 0, 0);
    if(wireFrame)
        glutWireCone(1.5, 2, slices, stacks);
    else
        glutSolidCone(1.5, 2, slices, stacks);
	glPopMatrix();

	if (inzitter)
    {
        glPushMatrix();
        glColor3f( 1.0, 0.0, 0.0);
        glTranslated(1.25+rijden, 2.25, 3.5);
        glRotated(-90, 1.0, 0.0, 0.0);
        gluCylinder(shirt, 1, 1, 2, slices, stacks);
        gluDisk(quadratic, 0, 1, slices, stacks);
        glTranslated(0.0, 0.0, 2.0);
        gluDisk(quadratic, 0, 1, slices, stacks);
        glPopMatrix();

        glPushMatrix();
        glTranslated(1.25+rijden, 5, 3.5);
        gluSphere(hoofd, 1.5, slices, stacks);
        glPopMatrix();
    }

    glDisable(GL_CLIP_PLANE0);
}

/*          Display fucntie
 *
 */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( Xlens, Ylens, Zlens, Xref, Yref, Zref, Xvw, Yvw, Zvw);
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();
    if(wireFrame)
        gluQuadricDrawStyle(quadratic, GLU_SILHOUETTE);
    else
        gluQuadricDrawStyle(quadratic, GLU_FILL);

    licht3[1] = spotHeight;

    glLightfv(	GL_LIGHT0,GL_POSITION,licht0);
    glLightfv(	GL_LIGHT1,GL_POSITION,licht1);
    glLightfv(	GL_LIGHT2,GL_POSITION,licht2);
    glLightfv(	GL_LIGHT3,GL_POSITION,licht3);
    glLightf(  GL_LIGHT3,GL_SPOT_CUTOFF,spotAngle);
    glLightf(  GL_LIGHT3,GL_SPOT_EXPONENT,spotExp);
    glLightfv(  GL_LIGHT3,GL_SPOT_DIRECTION,boogPlaats);

    if (axis)
    {
        axisFunc('z', 10.0);                 //z-as

        glPushMatrix();
        glRotatef(90.0, 0.0, 1.0, 0.0);
        axisFunc('x', 10.0);                 //x-as
        glPopMatrix();

        glPushMatrix();
        glRotatef(-90.0, 1.0, 0.0, 0.0);
        axisFunc('y', 10.0);                 //y-as
        glPopMatrix();
    }

    if (shading)
    {
        glShadeModel(GL_SMOOTH);
    }
    else
    {
        glShadeModel(GL_FLAT);
    }

    glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

    glMaterialf(GL_FRONT,GL_SHININESS,shininess);

    aankomst();
    zeepkist();
    if(more)
    {
        glTranslated(0.0, 0.0, -5.0);
        zeepkist();
    }
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glutSwapBuffers();
    glFlush();
}

void anim(void)
{
    if (wielDraai)
    {
        hoek -= wielDraai * 1.0;
        if ( hoek > 360.0)
            hoek -= 360.0;
        if ( hoek < -360.0)
            hoek += 360.0;
    }

    if (zeepRij)
    {
        rijden += zeepRij * 0.01;
        if (rijden > afgrond)
            rijden = startpunt;
    }
    glutSwapBuffers();
    glutPostRedisplay();
}


/*              De main functie
 *  Hier worden alle functies opgeroepen en worden alle OpenGL functies in een "loop" gezet
 */
int main(int argc, char *argv[])
{
    printf("Complexe Geometrie : Zeepkist \n");
    printf("Oproep argumenten : O(rthogonaal)   S(ymmetrisch perspectied   A(lgemeen) perspectief \n");

    if (argc > 1)
    {
        projection = argv[1][0];
    }
    else
    {
        projection = 'O';    /* default = Ortogonaal Perspectief */
    }

    printf("\nGekozen projectie : %c\nOOG    X           Y           Z\n", projection);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(10,10);

    glutCreateWindow("Complexe Geometrie : Zeepkist");

    glClearColor(0.8, 0.8, 0.8, 0.0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);

    glutCreateMenu(textureMenu);
    glutAddMenuEntry("Carrosserie : grijs", 1);
    glutAddMenuEntry("Carrosserie : witachtig", 2);
    glutAddMenuEntry("Onderstel : chrome", 3);
    glutAddMenuEntry("Onderstel : brons", 4);
    glutAddMenuEntry("Boog : geel", 5);
    glutAddMenuEntry("Boog : lila", 6);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    lichten();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(anim);

    glutMainLoop();
}
