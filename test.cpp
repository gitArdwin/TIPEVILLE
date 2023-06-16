#include "tipe1.cpp"
#include "affichage.cpp"


void test() {
  pers p1 = {{2, 3}, {"bit", 0, 1}, 100, 2};

  pers p2 = {{4, 7}, {"glaçons", 1, 1}, 200, 3};

  pers p3 = {{4, 7}, {"chibrons", 1, 1}, 50, 1};
  
  pers p4 = {{3, 8},{"bit", 0, 1} , 0 , 6 } ; 

  pers p5 = {{6,4},{"bit", 0, 1},0,2} ; 

  pers p6 = {{4,2},{"bit", 0, 1},0,2};

  pers p7 = {{4,5},{"bit", 0, 1},0,2} ; 

  pers p8 = {{3,3},{"bit", 0, 1},0,2} ; 

  pers p9 = {{2,4},{"bit", 0, 1},0, 5 } ; 

  pers p10 = {{2,6},{"bit", 0, 1},0,5 } ; 

  pers p11 = {{8,4},{"bit", 0, 1},0,5} ; 

  pers p12 = {{8,6},{"bit", 0, 1},0,5} ; 




  std::vector<produit> lp1;
  lp1.push_back({"bit", 0, 1});
  commerce c1 = {
      {1, 2},
      1,
      lp1,
  };
  std::vector<produit> lp2;
  lp2.push_back({"MARCEAUDEPAIN", 0, 1});
  commerce c2 = {{3, 3}, sqrtf(2), lp2};

  std::vector<produit> lp3;
  lp3.push_back({"Chienmaltraité", 0, 1});
  commerce c3 = {{1, 3}, sqrtf(3), lp3};

  commerce c4 = {{100, 100}, 1, lp3};

  commerce c5 = {{1, 2 }, 2, lp3};
  commerce c6 = {{2,6 }, 4 , lp3};
  commerce c7 = {{6, 8 }, 1 , lp3};
  commerce c8 = {{4.1 , 3.4} ,2 , lp3 } ; 
  commerce c9 = {{9,3.5},4,lp3} ; 
  commerce c10 = {{8,5},1,lp3};

  commerce petit1 =  {{0.2,0.2},0.10,lp3} ; 
  commerce petit2 =  {{9.8,0.2},0.10,lp3} ; 
  commerce petit3 =  {{9.8,9.8},0.10,lp3} ; 
  commerce petit4 =  {{0.2,9.8},0.10,lp3} ; 

  ville v = {{c1, c2, c3}, {p1}, {10, 10}

  };

  ville v2 = {{c1, c2, c3}, {p1, p2, p3}, {10, 10}

  };

  ville v3 = {{c4}, {p1, p2, p3}, {10, 10}};
  ville v4 = {{c10},{p9,p10, p11, p12},{10,10}} ; 
  // test sur les probas
  assert(egal(somme_normal(v, p1), 5.5));
  assert(egal(proba_pers_com(p1, c1, v), 0.0909));
  assert(egal(proba_pers_com(p1, c2, v), 0.3636));
  assert(egal(esperance_commerce(v2, c1), proba_pers_com(p1, c1, v2) +
                                              proba_pers_com(p2, c1, v2) +
                                              proba_pers_com(p3, c1, v2)));

  // test sur les collisions
  assert(!collision_com_com(c1, c4));
  assert(!collision_com_com(c1, c2));
  assert(collision_com_com(c2, c2));
  assert(!collision_com_ville(c1, v3));

  // dans l'avenir test_sur_meilleuremplacement
  coord res = meilleur_emplacement_quadriller(v4, 4 , lp3,10, {0,0}, v4.zone );
  printf("\n %f , %f \n ", res.x , res.y );
  v4.lc.push_back({{2,5},2,lp3});
  printf("\n %f \n", esperance_commerce(v4,v4.lc[1])) ; 
  v4.lc[1].c=res ; 
  printf("\n %f \n", esperance_commerce(v4,v4.lc[1]));

  commerce solution = {res,2, lp3  } ; 
  dessine_ville_solution (v4 , solution ) ; 

};

int main() {

  test();

  return 0;
}