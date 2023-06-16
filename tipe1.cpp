#include <algorithm>
#include <assert.h>
#include <iostream>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

bool egal(float a, float b) {
  // test d'égalité entre deux float à 10-3 pres
  return (a - b <= 0.001) && (b - a <= 0.001);
};
struct produit {
  std::string nom;
  int cle;
  int prix;
};

struct coord {
  float x;
  float y;
};

struct rect {
  coord a;
  coord b;
  coord c;
  coord d;
};

struct pers {
  coord c;
  produit prd;
  int bourse;
  int b;
};

struct commerce {
  coord c;
  float l;
  std::vector<produit> lprd;
};

struct ville {
  std::vector<commerce> lc;
  std::vector<pers> lp;
  coord zone;
};

bool egal_com(commerce com1, commerce com2) {

  return (egal(com1.c.x, com2.c.x) && egal(com1.c.y, com2.c.y) &&
          egal(com1.l, com2.l));
};

float distance(coord c1, coord c2) {

  return sqrtf(pow((c1.x - c2.x), 2) + pow((c1.y - c2.y), 2));
};

float somme_normal(ville v, pers p) {
  // celle qui est au dénominateur
  float res = 0;
  int i = 0;
  while (i < (v.lc).size()) {
    res = res + pow((v.lc[i]).l, 2) / pow(distance((v.lc[i]).c, p.c), p.b);
    i = i + 1;
  }
  return res;
};

float proba_pers_com(pers p, commerce com, ville v) {
  // probabilité qu'une personne p soit attiré par le commerce com dans la ville
  // v
  if (distance(com.c, p.c) == 0) {
    return 1.0;
  } 
  else {
    int i = 0;
    while (i < v.lc.size()) {
      if (distance(v.lc[i].c, p.c) == 0) {
        return 0;
      }
      i++;
    }
  }
  return (((com.l * com.l) / pow(distance(p.c, com.c), p.b)) /
          somme_normal(v, p));
};

float esperance_commerce(ville v, commerce com) {
  // le nombre de personne dans la ville v attiré par le commerce com

  float res = 0;
  int i = 0;
  while (i < v.lp.size()) {
    res = res + proba_pers_com(v.lp[i], com, v);
    i = i + 1;
  }
  return res;
};

rect get_rect_from_com(commerce com) {
  // retrourne les coordonnées a b c d du carré que forme com
  rect r = {{com.c.x - (com.l) / 2, com.c.y + (com.l) / 2},
            {com.c.x + (com.l) / 2, com.c.y + (com.l) / 2},
            {com.c.x + (com.l) / 2, com.c.y - (com.l) / 2},
            {com.c.x - (com.l) / 2, com.c.y - (com.l) / 2}};
  return r;
};

bool collision_com_com(commerce com1, commerce com2) {
  // retourne si le com1 est en collision com2
  if (com1.l < com2.l) {
    commerce temp = com2;
    com2 = com1;
    com1 = temp;
  };

  // com1 est plus grand que com2
  rect r1 = get_rect_from_com(com1);
  rect r2 = get_rect_from_com(com2);

  return (((r1.a.x <= r2.a.x) && (r2.a.x <= r1.b.x) && (r1.d.y <= r2.a.y) &&
           (r2.a.y <= r1.a.y)) ||
          ((r1.a.x <= r2.b.x) && (r2.b.x <= r1.b.x) && (r1.d.y <= r2.b.y) &&
           (r2.b.y <= r1.a.y)) ||
          ((r1.a.x <= r2.c.x) && (r2.c.x <= r1.b.x) && (r1.d.y <= r2.c.y) &&
           (r2.c.y <= r1.a.y)) ||
          ((r1.a.x <= r2.d.x) && (r2.d.x <= r1.b.x) && (r1.d.y <= r2.d.y) &&
           (r2.d.y <= r1.a.y)));
};

bool collision_com_ville(commerce com1, ville v) {
  // retourne si com1 est en collision avec un commerce de la ville v
  int l = v.lc.size();
  int i = 0;
  while (i < l) {
    if (collision_com_com(com1, v.lc[i])) {
      // si ils sont en collision mais ne sont pas égales
      return true;
    };
    i = i + 1;
  };
  return false;
};

coord meilleur_emplacement_quadriller(ville v, float s,
                                      std::vector<produit> lprd,
                                      float decoupage, coord basgauche,
                                      coord hautdroit) {
  // retourne le meilleur emplacement pour un commerce selon un quadrillage à
  // définir dans la zone de la ville v délimité par les points basgauche et
  // hautdroit qui forme un carrée

  float i = basgauche.x;
  float p = ((hautdroit.x - basgauche.x) / decoupage);
  if (p <= 0) {
    printf("\n WTF \n ");
  };
  commerce com = {{0, 0}, s, lprd};
  commerce copie = {{0, 0}, s, lprd};
  float res_esperance = 0;
  while (i < hautdroit.x) {
    float j = basgauche.y;
    while (j < hautdroit.y) {
      copie.c.x = i;
      copie.c.y = j;
      v.lc.push_back(copie);
      float temp = esperance_commerce(v, copie);
      v.lc.pop_back();
      if ((res_esperance < temp) && (!collision_com_ville(copie, v))) {
        res_esperance = temp;
        com.c = copie.c;
      };
      j = j + p;
    };
    i = i + p;
  };
  return com.c;
};

coord meilleur_emplacement_repeter(ville v, float s, std::vector<produit> lprd,
                                   float decoupage, int n) {
  // retourne le meilleur emplacement pour un commerce selon un guadrillage
  // défini par découpage et une répition n
  int i = 0;
  coord basgauche = {0, 0};
  coord hautdroit = v.zone;
  coord res = {0, 0};
  float d = v.zone.x;
  while (i < n) {
    res = meilleur_emplacement_quadriller(v, s, lprd, decoupage, basgauche,
                                          hautdroit);
    hautdroit.x = res.x + (d / decoupage);
    hautdroit.y = res.y + (d / decoupage);
    basgauche.x = res.x - (d / decoupage);
    basgauche.y = res.y - (d / decoupage);
    d = hautdroit.x - basgauche.x;
    i = i + 1;
  };
  return res;
}
