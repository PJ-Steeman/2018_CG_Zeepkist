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

#include "zeepkist.h"
#include "../JPEG/InitJPG.h"

GLubyte projection = 'S';
GLdouble scale = 1;

GLdouble Xmin = -5, Xmax = 10, Ymin = -3, Ymax = 12;
GLdouble Near = 1.0, Far = 250.0;

GLdouble Xlens = -20.0, Ylens = 3.0, Zlens = 0.0;       //locatie lens
GLdouble Xref = 0.0, Yref = 0.0, Zref = 0.0;            //referentie punt voor de lens(naar waar kijkt men)
GLdouble Xvw = 0.0, Yvw = 1.0, Zvw = 0.0;               //in welk valk kijk men(hier staat de y-as naar boven)

GLuint texName[AANT];
char beeldnaam[AANT][80] = {"bliksem.jpeg", "rainbow.jpg"};

GLfloat licht0[] = {10.0, 10.0, 5.0, 0.0};              /* Locaties van de lichten */
GLfloat licht1[] = {-10.0, 10.0, 10.0, 0.0};
GLfloat licht2[] = {5.0, 10.0, 10.0, 0.0};
GLfloat licht3[] = {0.0, 7.5, 0.0, 1.0};

GLfloat wielen[AANTWIELEN][3] = {{0, 1.5, 0},{0, 1.5, 6.5},{9.25, 1.5, 3.25}};

GLint slices = 16;  //verticale opdeling
GLint stacks = 16;  //horizontale opdeling

GLint shading = 0;      /* 0 = FLAT   1 = SMOOTH */

GLfloat spotAngle = 30.0;
GLfloat spotExp = 20.0;
GLfloat spotHeight = 0.0;
GLfloat boogPlaats[] = {15.0, 7.5, 1, 1.0};

GLdouble shininess = 10.0;
GLfloat hoek = 0.0;
GLfloat rijden = 0.0;

GLfloat afgrond = 100.0;
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
GLint details = 0;      /* 0 = UIT   1 = AAN*/

GLint carrMat = 1;
GLint ondMat = 1;
GLint boogMat = 1;


/*          Toetsen Functie
 * x/X - y/Y - z/Z verplaatsen oog
 * a/A - b/B - c/C - d/D aan/uitschakelen lichtbronnen
 * s/S keuze FLAT en SMOOTH shading
 * v/V verkleinen/vergroten spothoek
 * w/W aanpassen spot expontent (stappen van 5 met initiÍle waarde = 20)
 * h/H aanpassen hoogte van de spot
 * e/E aanpassen shininess (stappen van 5 met initiÍle waarde = 10)
 * l zichtbaarheid draadmodellen
 * j assen
 * k controlepunten van de oppervlaken
 * n meerdere zeepkisten
 * f doorzichtig maken van carrosserie
 * t jpeg textuur van de carroserrie en de boog
 * g draaien van de wielen
 * G bewegen van de zeepkist
 * m mist
 * M exponentiÍel effect mist
 * d locatie van lichtbronnen weergeven
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
	case 'p' : details = !details;          break;
	case 'f' : seeThrough = !seeThrough;    break;
	case 't' : jpegTexture = !jpegTexture;  break;
	case 'g' : wielDraai = !wielDraai;      break;
	case 'G' : zeepRij = !zeepRij;          break;
	case 'm' : fog = !fog;                  break;
	case 'M' : fogExp = !fogExp;            break;

	case 27 :
    	case 'q': exit(0);			break;
    }
    printf("        %5.1f       %5.1f       %5.1f                        %5.1f       %5.1f        %5.1f\n", Xlens, Ylens, Zlens, spotAngle, spotExp, spotHeight );
    glutPostRedisplay();
}

/*          Lichten Functie
 *
 */
void lichten(void)
{
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, zwart);      // eerst alles op zwart zetten zodat er niets per ongeluk al een kleur heeft
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


/*          Herschaal Functie
 * raam : O(rtogonaal)  S(ymmetrisch) perspectief   A(lgemeen) perspectief
 */
void resize(GLint newWidth, GLint newHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    switch (projection)
    {
        case 'A':
        case 'a':
            glFrustum(Xmin/10, Xmax/10, Ymin/10, Ymax/10, Near, Far);       //omdat de zeepist anders te ver staat
            break;
        case 'O':
        case 'o':
            glOrtho(Xmin, Xmax, Ymin, Ymax, Near, Far);
            break;
        default:
        case 'S':
        case 's':
            gluPerspective(75.0, 1.0, Near, Far);		//field of view, y scale, near, far
            break;
    }
    glViewport(0, 0, newWidth, newHeight);

    if (newWidth < newHeight * scale)
        glViewport(0,0, newWidth*scale, newWidth);
    else
        glViewport(0,0, newHeight*scale, newHeight);
}

/*          Material Mapping
 *
 */
void materiaalMenu(GLint keuze)
{
    switch(keuze)
    {
        case 1: carrMat = 1;
            break;
        case 2: carrMat = 0;
            break;
        case 3: ondMat = 1;
            break;
        case 4: ondMat = 0;
            break;
        case 5: boogMat = 1;
            break;
        case 6: boogMat = 0;
            break;
        case 7: exit(0);
    }
    glutPostRedisplay();
}

int nurbsError(GLenum errorCode)
{
   const GLubyte *estring;

   estring = gluErrorString(errorCode);
   fprintf (stderr, "Nurbs Error: %s\n", estring);
   exit (0);
}

/*          Tekenen 1/4 boog
 *  tekent via een bspline 1/4 van de boog
 */
void deelBoog(void)
{
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_MAP2_TEXTURE_COORD_2);
    GLUnurbsObj *spline;
    spline = gluNewNurbsRenderer();
    gluNurbsProperty(spline, GLU_SAMPLING_TOLERANCE, 100.0);        //hoe hoger, hoe "ruwer"
    gluNurbsCallback(spline, GLU_ERROR, (_GLUfuncptr)nurbsError);

    if(wireFrame)
        gluNurbsProperty(spline, GLU_DISPLAY_MODE, GLU_OUTLINE_POLYGON);    //lijkt van ver een volle vorm, maar als men dichter gaat
                                                                            //kan men de wirefame zien (hoge densiteit door sampling tolerance)
    else
        gluNurbsProperty(spline, GLU_DISPLAY_MODE, GLU_FILL);

    glPushMatrix();
    gluBeginSurface(spline);

    glBindTexture (GL_TEXTURE_2D,texName[1]);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    if(jpegTexture)
        gluNurbsSurface(spline, AANTKNOTS, knots, AANTKNOTS, knots, 4 * 3, 3, &splinepunten[0][0][0], SPLINEGROOTTE, SPLINEGROOTTE, GL_MAP2_TEXTURE_COORD_2);

    gluNurbsSurface(spline, AANTKNOTS, knots, AANTKNOTS, knots, 4 * 3, 3, &splinepunten[0][0][0], SPLINEGROOTTE, SPLINEGROOTTE, GL_MAP2_VERTEX_3);
    //nurbs,#knots u,knotvalues,#knots v,knotvalues, u offset tussen punten, v offset,punten,#punten u, # v,type surface

    gluEndSurface(spline);
    glPopMatrix();

    if (checkPoints)
    {
        GLint i,j;

        glPointSize(5.0);
        glDisable(GL_LIGHTING);
        glColor3f(0.0, 1.0, 1.0 );
        glBegin(GL_POINTS);
        for (i = 0; i < 4; i++)
            for (j = 0; j < 4; j++)
                glVertex3f(splinepunten[i][j][0], splinepunten[i][j][1], splinepunten[i][j][2]);
        glEnd();
        glEnable(GL_LIGHTING);
    }
    glDisable(GL_MAP2_TEXTURE_COORD_2);
    glDisable(GL_MAP2_VERTEX_3);
}

/*          Aankomst functie
 *  tekent de aankomst(2 cilinders en 4 keer deelboog) en geeft het zijn materiaaleigenschappen
 */
void aankomst(void)
{
    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    if(wireFrame)
        gluQuadricDrawStyle(quadratic, GLU_SILHOUETTE);
    else
        gluQuadricDrawStyle(quadratic, GLU_FILL);

    if(boogMat)
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

    if(jpegTexture)
    {
    	glBindTexture (GL_TEXTURE_2D,texName[1]);
    	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	gluQuadricTexture(quadratic,GL_TRUE);
    	glEnable(GL_TEXTURE_2D);
    }

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();                         //linker cilinder
    glTranslated(50, 0, -13);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(quadratic, 1, 1, 7.5, slices, stacks);
    gluDisk(quadratic, 0, 1.0, slices, stacks);
    glTranslated(0.0, 0.0, 0.5);
    gluDisk(quadratic, 0, 1.0, slices, stacks);
    glPopMatrix();

    glPushMatrix();                         //rechter cilinder
    glTranslated(50, 0, 20);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(quadratic, 1, 1, 7.5, slices, stacks);
    gluDisk(quadratic, 0, 1.0, slices, stacks);
    glTranslated(0.0, 0.0, 0.5);
    gluDisk(quadratic, 0, 1.0, slices, stacks);
    glPopMatrix();

    deelBoog();

    glPushMatrix();
    glScalef(-1,1,1);
    glTranslated(-100,0,0);
    deelBoog();
    glPopMatrix();

    glPushMatrix();
    glScalef(-1,1,-1);
    glTranslated(-100,0,-7);
    deelBoog();
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,-1);
    glTranslated(0,0,-7);
    deelBoog();
    glPopMatrix();

    if(jpegTexture)
        glDisable(GL_TEXTURE_2D);
        gluQuadricTexture(quadratic,GL_FALSE);

    gluDeleteQuadric(quadratic);
}
/*          Carrosserie
 *  tekent via een bezier opp. 1/2 van de carrosserie
 */
void carroserie(void)
{
    GLint k, l;
    glEnable(GL_MAP2_VERTEX_3);
    glEnable(GL_MAP2_TEXTURE_COORD_2);
    glMapGrid2f(slices, 0.0, 1.0, stacks, 0.0, 1.0);

    if(jpegTexture)
    {
    	glEnable(GL_TEXTURE_2D);

    	glBindTexture (GL_TEXTURE_2D,texName[0]);
    	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

    	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 3, BEZIERLENGTE, 0, 1, BEZIERLENGTE*3, BEZIERBREEDTE, &bezierpunten[0][0][0]); //target,0,1, "delen", hoeveelheid lengte,0,1,delen(3*6), hoeveelheid breedte);
    }
    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, BEZIERLENGTE, 0, 1, BEZIERLENGTE*3, BEZIERBREEDTE, &bezierpunten[0][0][0]); //target,0,1, "delen", hoeveelheid lengte,0,1,delen(3*6), hoeveelheid breedte);

    if(seeThrough)
    {
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);      //dieptebuffer
    }

    if(carrMat)
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

    if(wireFrame)
        glEvalMesh2(GL_LINE,0,slices,0,stacks);

    else
        glEvalMesh2(GL_FILL,0,slices,0,stacks);

    if(seeThrough)
    {
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }

    if(jpegTexture)
    	glDisable(GL_TEXTURE_2D);

    if(checkPoints)
    {
        glPushMatrix();
        glPointSize(5.0);
        glDisable(GL_LIGHTING);
        glColor3f(1.0, 1.0, 0.0);
        glBegin(GL_POINTS);
        for (l = 0; l < 6; l++)
            for (k = 0; k < 4; k++)
                glVertex3fv(&bezierpunten[k][l][0]);
        glEnd();
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }
    glDisable(GL_MAP2_VERTEX_3);
    glDisable(GL_MAP2_TEXTURE_COORD_2);
}

/*          Zeepkist Functie
 *  Deze tekent de zeekpist(onderstel + 2 keer carrosserie) en geeft het ook zijn materiaaleigenschappen
 */

void zeepkist(void)
{
    glEnable(GL_LIGHTING);

    GLUquadricObj *quadratic;
    quadratic = gluNewQuadric();

    if(wireFrame)
        gluQuadricDrawStyle(quadratic, GLU_SILHOUETTE);
    else
        gluQuadricDrawStyle(quadratic, GLU_FILL);

    if(ondMat)
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

    glPushMatrix();                         //voorstuk onderstel
    glTranslated(5+rijden, 1.5, 3.0);
    glScaled(19.0, 1.0, 1.0);
    if(wireFrame)
        glutWireCube(0.5);
    else
        glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(5+rijden, 1.5, 4.0);
    glScaled(19.0, 1.0, 1.0);
    if(wireFrame)
        glutWireCube(0.5);
    else
        glutSolidCube(0.5);
    glPopMatrix();

    glPushMatrix();                         //achterstuk onderstel
    glTranslated(0+rijden, 1.5, 3.5);
    glScaled(1.0, 1.0, 12.0);
    if(wireFrame)
        glutWireCube(0.5);
    else
        glutSolidCube(0.5);
    glPopMatrix();

    glDisable(GL_LIGHTING);                 //om de banden en het zitje steeds dezelfde kleur te doen hebben

    glColor3f(0.3, 0.3, 0.3);
    GLint teller;
    for( teller = 0; teller < AANTWIELEN; teller ++)       //wielen
    {
        glPushMatrix();
        glTranslated(wielen[teller][0]+rijden, wielen[teller][1], wielen[teller][2]);
        glRotatef(hoek, 0.0, 0.0, 1.0);
        gluCylinder(quadratic, 1.5, 1.5, 0.5, slices, stacks);
        gluDisk(quadratic, 0, 1.5, slices, stacks);
        glTranslated(0.0, 0.0, 0.5);
        gluDisk(quadratic, 0, 1.5, slices, stacks);
        glPopMatrix();
    }

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
    gluDisk(quadratic, 0, 1.5, slices, stacks);
    glPopMatrix();

    glDisable(GL_CLIP_PLANE0);
    glEnable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(0+rijden, 0.2, 3.5);
    carroserie();
    glPopMatrix();

    glPushMatrix();
    glScalef(1,1,-1);
    glTranslated(0+rijden, 0.2, -3.5);
    carroserie();
    glPopMatrix();

    glDisable(GL_LIGHTING);

    glColor3f(0.6, 0.6, 0.6);
    glPushMatrix();
    glBegin(GL_QUADS);
        glTexCoord3f(0,0,0);    glVertex3f(startpunt,0,-1);
        glTexCoord3f(0,0,1);    glVertex3f(afgrond,0,-1);
        glTexCoord3f(1,0,1);    glVertex3f(afgrond,0,8.5);
        glTexCoord3f(1,0,0);    glVertex3f(startpunt, 0, 8.5);
    glEnd();
    glPopMatrix();

    gluDeleteQuadric(quadratic);

    glFlush();
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

    licht3[1] = spotHeight;

    glLightfv(GL_LIGHT0,GL_POSITION,licht0);
    glLightfv(GL_LIGHT1,GL_POSITION,licht1);
    glLightfv(GL_LIGHT2,GL_POSITION,licht2);
    glLightfv(GL_LIGHT3,GL_POSITION,licht3);
    glLightf(GL_LIGHT3,GL_SPOT_CUTOFF,spotAngle);
    glLightf(GL_LIGHT3,GL_SPOT_EXPONENT,spotExp);
    glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION,boogPlaats);

    glFogfv(GL_FOG_COLOR, mist);

    if(fogExp)
        glFogf(GL_FOG_MODE, GL_EXP);
    else
        glFogf(GL_FOG_MODE, GL_LINEAR);

    glFogf(GL_FOG_DENSITY, 0.02);
    glFogf(GL_FOG_START, 0.0);
    glFogf(GL_FOG_END, 200);

    if(details)
    {
        glPointSize(7.0);
        glColor3f(1.0, 0.0, 1.0 );
        glBegin(GL_POINTS);
            glVertex3f(licht0[0], licht0[1], licht0[2]);
            glVertex3f(licht1[0], licht1[1], licht1[2]);
            glVertex3f(licht2[0], licht2[1], licht2[2]);
            glVertex3f(licht3[0], licht3[1], licht3[2]);
        glEnd();
    }

    if(fog)
        glEnable(GL_FOG);

    if (axis)
    {
        glBegin(GL_LINES);
            glColor3f(0.0, 0.1, 0.8);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(10, 0.0, 0.0);

            glColor3f(0.0, 0.8, 0.1);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(0.0, 10, 0.0);

            glColor3f(0.8, 0.1, 0.0);
            glVertex3d(0.0, 0.0, 0.0);
            glVertex3d(0.0, 0.0, 10);
        glEnd();
    }

    if (shading)
        glShadeModel(GL_SMOOTH);
    else
        glShadeModel(GL_FLAT);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glMaterialf(GL_FRONT,GL_SHININESS,shininess);

    aankomst();
    zeepkist();

    if(more)
    {
        glTranslated(0.0, 0.0, -9);
        zeepkist();
        glTranslated(0.0, 0.0, 18);
        zeepkist();
    }

    if(fog)
        glDisable(GL_FOG);

    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    glutSwapBuffers();
    glFlush();
}
/*          Animatie Functie
 *  Afhankelijk van de snelheid van de computer zal de zeepkist sneller of trager rijden.
 *  Een parameter wordt stapsgewijs verhoogd. Tijdens het tekenen wordt er met deze parameter geroteerd of getransleerd.
 *  Hierdoor lijkt het alsof de zeepkist rijdt en de wielen draaien.
 */
void anim(void)
{
    if (wielDraai)
    {
        hoek -= wielDraai * 1.0;
        if (hoek < -360.0)
            hoek += 360.0;
    }

    if (zeepRij)
    {
        rijden += zeepRij * 1.0;
        if (rijden > afgrond)
            rijden = startpunt;
    }
    glutPostRedisplay();
}


/*              De main functie
 *  Hier worden alle functies opgeroepen en worden alle OpenGL functies in een "loop" gezet
 */
int main(int argc, char *argv[])
{
    printf("Complexe Geometrie : Zeepkist \n");
    printf("Oproep argumenten : O(rthogonaal)   S(ymmetrisch) perspectief   A(lgemeen) perspectief \n");

    if (argc > 1)
        projection = argv[1][0];
    else
        projection = 'S';    /* default = Symmetrisch Perspectief */

    printf("\nGekozen projectie : %c\n", projection);
    printf("\nLicht Locaties : \nAmbient Licht: [%.0f %.0f %.0f]      Diffuus Licht: [%.0f %.0f %.0f]      ", licht0[0], licht0[1], licht0[2], licht1[0], licht1[1], licht1[2]);
    printf("Specular Licht: [%.0f %.0f %.0f]       Spot: [%.0f %.0f %.0f]\n", licht2[0], licht2[1], licht2[2], licht3[0], licht3[1], licht3[2]);
    printf("\nCamera:    X           Y           Z                Spot:     Hoek      Exponent      Hoogte\n");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000,1000);
    glutInitWindowPosition(10,10);

    glutCreateWindow("Complexe Geometrie : Zeepkist");

    glClearColor(0.8, 0.8, 0.8, 0.0);
    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);


    GLint caromen = glutCreateMenu(materiaalMenu);
    glutAddMenuEntry("Grijs", 1);
    glutAddMenuEntry("Witachtig", 2);

    GLint ondmen = glutCreateMenu(materiaalMenu);
    glutAddMenuEntry("Chrome", 3);
    glutAddMenuEntry("Brons", 4);

    GLint boogmen = glutCreateMenu(materiaalMenu);
    glutAddMenuEntry("Geel", 5);
    glutAddMenuEntry("Lila", 6);

    glutCreateMenu(materiaalMenu);
    glutAddSubMenu("Carrosserie", caromen);
    glutAddSubMenu("Onderstel", ondmen);
    glutAddSubMenu("Boog", boogmen);
    glutAddMenuEntry("EXIT",7);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    lichten();

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(anim);

    tImageJPG *pImage;
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
   	glGenTextures(AANT, texName);
	for(GLint i=0;i< AANT;i++)
	{
		pImage = LoadJPG(beeldnaam[i]);
	        fprintf(stderr, "prent %s : %d x %d\n", beeldnaam[i], pImage->sizeX, pImage->sizeY);
	        glBindTexture (GL_TEXTURE_2D,texName[i]);
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pImage->sizeX, pImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pImage->data);
		//target,level,format,width,height,border,format,type, data
	}

    glutMainLoop();
}
