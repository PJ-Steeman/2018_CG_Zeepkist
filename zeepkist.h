#define esc 27          //escape toets code
#define AANT 2          //aantal afbeeldingen
#define BEZIERLENGTE 6
#define BEZIERBREEDTE 4
#define SPLINEGROOTTE 4
#define AANTKNOTS 8
#define AANTWIELEN 3

/*
 *	    BEZIER EN BSPLINE PUNTEN
 */

GLfloat bezierpunten[BEZIERBREEDTE][BEZIERLENGTE][3] =   {{{12, 0.0, 0},{5, 0.0, 2},{4,0.0,3},{2 ,0.0,3.5},{0,0.0,3.5},{-2,0.0,4}},
                                   {{12, 1, 0},{5, 1, 2},{4,1.5,4.25},{2,1,4},{0,1,4},{-2, 1,4}},
                                   {{12, 1.5, 0.5},{5, 1.5, 2.5},{4,2.5,2.5},{2,2.5,6},{0,2.5,6},{-2,2.5,5}},
                                   {{12, 2, 0.25},{5,2,0},{4,3,0.75},{2,4,4},{0,4,1.5},{-2,4,0}}};

GLfloat splinepunten[SPLINEGROOTTE][SPLINEGROOTTE][3] = {{{49.5,6,-13.5},{49,8,-13.5},{49,8,-12.5},{49.5,6,-12.5}},
                                 {{49.3,8,-14},{47,13.5,-7.5},{45,15,35},{49.3,8,-12}},
                                 {{49.6,8,-14},{52,13.5,-7.5},{55,15,35},{49.6,8,-12}},
                                 {{50,6,-14},{50,8,-13.5},{50,8,-12.5},{50,6,-12}}};

GLfloat knots[AANTKNOTS] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};    // gewichtsfactor voor ieder punt


/*
 *      TOEKENNEN VAN KLEUREN EN MATERIALEN
 */

GLfloat wit[] = {1.0,1.0,1.0,1.0};
GLfloat groen[] = {0.0,1.0,0.0,1.0};
GLfloat blauw[] = {0.0,0.0,1.0,1.0};
GLfloat rood[] = {1.0,0.0,0.0,1.0};
GLfloat geel[] = {1.0,1.0,0.0,1.0};
GLfloat zwart[] = {0.0,0.0,0.0,1.0};
GLfloat mist[] = {0.7,0.7,0.7,1.0};

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
