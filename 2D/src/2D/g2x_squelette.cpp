/*=================================================================*/
/*= E.Incerti - eric.incerti@univ-eiffel.fr                       =*/
/*= Université Gustave Eiffel                                     =*/
/*= Code "squelette" pour prototypage avec libg2x.6c              =*/
/*=================================================================*/

#include <g2x.h>
#include "MovingParticle.hpp"
#include "FixedParticle.hpp"
#include "Spring.hpp"
#include "Gravity.hpp"
#include <vector>
#include <iostream>

/* tailles de la fenêtre (en pixel) */
static int WWIDTH = 512, WHEIGHT = 512;
/* limites de la zone reelle associee a la fenetre */
static double wxmin = -10., wymin = -10., wxmax = +10., wymax = +10.;

static std::vector<ParticleInterface *> particles;

static std::vector<LinkInterface *> links;

double Fe = 100; //à régler à volonté
double h = 1.;
double m = 1; // constant
double k = 0.1; // dans [0,1]
double z = 0.01; // [0,0.1]

void initParticlesAndLinks()
{
	particles.emplace_back(new FixedParticle(Particle(g2x_Vector_XY(-3,0), 1, G2Xcolor{0, 1, 0, 0})));
	for(int y = -2; y<3;y++)
	{
		particles.emplace_back(new MovingParticle{Particle(g2x_Vector_XY(y,0), 1, G2Xcolor{1, 0, 0, 0}) });
	}
	particles.emplace_back(new FixedParticle(Particle(g2x_Vector_XY(3,0), 1, G2Xcolor{0, 1, 0, 0})));
	for(int i = 0; i<particles.size()-1;i++)
	{
		links.emplace_back(new Spring(Link{*particles[i],*particles[i+1]}));
		links.emplace_back(new Gravity(Link{*particles[i],*particles[i+1]}));
	}
}

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
	/* zone graphique reelle associee a la fenetre                 */
	/* si cette fonction n'est pas appelée, les valeurs par défaut */
	/* sont (-1.,-1)->(+1.,+1.)                                    */
	g2x_SetWindowCoord(wxmin, wymin, wxmax, wymax);
	initParticlesAndLinks();
	int id=g2x_CreateScrollv_d("Fe",&Fe,0,1000,1.0,"Fe");
  	g2x_SetScrollColor(id,G2Xgb_c);
	id=g2x_CreateScrollv_d("k",&k,0,1,0.1,"k");
  	g2x_SetScrollColor(id,G2Xgb_c);
	id=g2x_CreateScrollv_d("z",&z,0,0.1,0.01,"z");
  	g2x_SetScrollColor(id,G2Xgb_c);
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
	for (LinkInterface *link : links)
	{
		link->draw();
	}
	for (ParticleInterface *particle : particles)
	{
		particle->draw();
	}
}

/* la fonction d'animation (facultatif) */
static void anim(void)
{
	for (LinkInterface *link : links)
	{
		link->integrate(k* m * Fe * Fe,z * m * Fe);
	}
	for (ParticleInterface *particle : particles)
	{
		particle->integrate(h/Fe);
	}
}

/* la fonction de sortie  (facultatif) -- atexit() */
static void quit(void)
{
}

/***************************************************************************/
/* La fonction principale : NE CHANGE JAMAIS                               */
/***************************************************************************/
int main(int argc, char **argv)
{
	/* creation de la fenetre - titre et tailles (pixels) */
	g2x_InitWindow(*argv, WWIDTH, WHEIGHT);
	g2x_SetInitFunction(init); /* fonction d'initialisation */
	g2x_SetDrawFunction(draw); /* fonction de dessin        */
	g2x_SetAnimFunction(anim); /* fonction d'animation      */
	g2x_SetExitFunction(quit); /* fonction de sortie        */
							   /* lancement de la boucle principale */
	return g2x_MainStart();
	/* RIEN APRES CA */
}
