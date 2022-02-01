/*=================================================================*/
/*= E.Incerti - eric.incerti@univ-eiffel.fr                       =*/
/*= Université Gustave Eiffel                                     =*/
/*= Code "squelette" pour prototzpage avec libg2x.6c              =*/
/*=================================================================*/

#include <g3x.h>
#include "MovingParticle.hpp"
#include "FixedParticle.hpp"
#include "Spring.hpp"
#include "Gravity.hpp"
#include "Wind.hpp"
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
double m = 1;				  // constant
double k = 0.1 * m * Fe * Fe; // dans [0,1]
double z = 0.01 * m * Fe;	  // [0,0.1]
int size = 11;

void initFlag()
{
	for (int x = 0; x < size; x++)
	{
		for (int zc = 0; zc < size; zc++)
		{
			if (x == 0)
			{
				particles.emplace_back(new FixedParticle(Particle(G3Xvector{(double)x,0 , (double)zc}, 1, G3Xcolor{0, 0, 0, 0})));
			}
			else
			{
				particles.emplace_back(new MovingParticle{Particle(G3Xvector{(double)x, 0, (double)zc}, 1, G3Xcolor{0, 0, 0, 0})});
			}
		}
	}
	int i = 0;
	for (int x = 0; x < size; x++)
	{
		k = pow(x-size, 2) / (pow(size, 2)) * 0.1 * m * Fe * Fe;
		for (int zc = 0; zc < size; zc++)
		{
			links.emplace_back(new Gravity(Link{*particles[i], *particles[i], G3Xcolor{1, 1, 1}}));
			links.emplace_back(new Wind(Link{*particles[i], *particles[i], G3Xcolor{1, 1, 1}}));
			if (x < size - 1 && zc < size - 1)
			{
				links.emplace_back(new Spring(Link{*particles[i], *particles[i + size + 1], G3Xcolor{0, 0, 0}}, k, z));
			}
			if (x < size - 1 && zc > 0)
			{
				links.emplace_back(new Spring(Link{*particles[i], *particles[i + size - 1], G3Xcolor{0, 0, 0}}, k, z));
			}
			if (zc < size - 1)
			{
				links.emplace_back(new Spring(Link{*particles[i], *particles[i + 1], G3Xcolor{1, 1, 1}}, k, z));
			}
			if (x < size - 1)
			{
				links.emplace_back(new Spring(Link{*particles[i], *particles[i + size], G3Xcolor{1, 1, 1}}, k, z));
			}
			if (zc%2 == 0 && zc<size-1)
			{
				links.emplace_back(new Spring(Link{*particles[i], *particles[i + 2], G3Xcolor{0, 0, 0}}, k, z));
			}
			if (x%2==0 && x<size-1)
			{
				links.emplace_back(new Spring(Link{*particles[i], *particles[i + size * 2], G3Xcolor{0, 0, 0}}, k, z));
			}
			i++;
		}
	}
}

void reset()
{
	for (LinkInterface *link : links)
	{
		delete link;
	}
	for (ParticleInterface *particle : particles)
	{
		delete particle;
	}
	particles.clear();
	links.clear();
	initFlag();
}

/* la fonction d'initialisation : appelée 1 seule fois, au début */
static void init(void)
{
	/* zone graphique reelle associee a la fenetre                 */
	/* si cette fonction n'est pas appelée, les valeurs par défaut */
	/* sont (-1.,-1)->(+1.,+1.)                                    */
	initFlag();
	/*
	int id=g3x_CreateScrollv_d("Fe",&Fe,0,1000,1.0,"Fe");
	g3x_SetScrollColor(id,G3Xgb_c);
	id=g3x_CreateScrollv_d("k",&k,0,1,0.1,"k");
	g3x_SetScrollColor(id,G3Xgb_c);
	*/
	int id=g3x_CreateScrollv_d("z",&z,0,0.1 * m * Fe,0.01 * m * Fe,"z");
	g3x_SetScrollColor(id,G3Xgb_c);
	g3x_SetKeyAction('r',reset,nullptr);
}

/* la fonction de dessin : appelée en boucle */
static void draw(void)
{
	glDisable(GL_LIGHTING);
	glPointSize(1);
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
		link->integrate();
	}
	for (ParticleInterface *particle : particles)
	{
		particle->integrate(h / Fe);
	}
}

/* la fonction de sortie  (facultatif) -- atexit() */
static void quit(void)
{
	for (LinkInterface *link : links)
	{
		delete link;
	}
	for (ParticleInterface *particle : particles)
	{
		delete particle;
	}
}

/***************************************************************************/
/* La fonction principale : NE CHANGE JAMAIS                               */
/***************************************************************************/
int main(int argc, char **argv)
{
	/* creation de la fenetre - titre et tailles (pixels) */

	g3x_InitWindow(*argv, WWIDTH, WHEIGHT);
	g3x_SetPerspective(40., 1000., 1.);
	g3x_SetCameraCartesian({-size*3.,size*2.,0},{size/2.,0,size/2.});
	g3x_SetInitFunction(init); /* fonction d'initialisation */
	g3x_SetDrawFunction(draw); /* fonction de dessin        */
	g3x_SetAnimFunction(anim); /* fonction d'animation      */
	g3x_SetExitFunction(quit); /* fonction de sortie        */
	return g3x_MainStart();
}
