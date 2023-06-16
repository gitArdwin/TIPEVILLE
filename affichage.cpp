
#include <SFML/Graphics.hpp>


void dessine_ville(ville v) {
  // dessine une ville
  sf::RenderWindow window(sf::VideoMode(100*v.zone.x, 100*v.zone.y ), "My window");

  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // clear the window with black color
    window.clear(sf::Color::White);

    // draw everything here...

    int i = 0;
    while (i < v.lc.size()) {
      sf::RectangleShape rectangle(sf::Vector2f(v.lc[i].l*100, v.lc[i].l*100));
      rectangle.setFillColor(sf::Color(255, 255, 255, 150  ));
      rectangle.setPosition((v.lc[i].c.x - (v.lc[i].l) / 2 )*100,
                            ((v.zone.y - v.lc[i].c.y) - (v.lc[i].l) / 2)*100);
      rectangle.setOutlineColor(sf::Color::Black);
      rectangle.setOutlineThickness(4) ; 
      window.draw(rectangle);
      i++;
    } 

    // end the current frame
    window.display();
  }
};


void dessine_ville_solution (ville v, commerce com ) {
  // dessine une ville
  sf::RenderWindow window(sf::VideoMode(100*v.zone.x, 100*v.zone.y ), "My window");

  // run the program as long as the window is open
  while (window.isOpen()) {
    // check all the window's events that were triggered since the last
    // iteration of the loop
    sf::Event event;
    while (window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed)
        window.close();
    }

    // clear the window with black color
    window.clear(sf::Color::White);

    // draw everything here...

    // dessine les commerces 
    int i = 0;
    while (i < v.lc.size()) {
      sf::RectangleShape rectangle(sf::Vector2f(v.lc[i].l*100, v.lc[i].l*100));
      rectangle.setFillColor(sf::Color(255, 255, 255, 150  ));
      rectangle.setPosition((v.lc[i].c.x - (v.lc[i].l) / 2 )*100,
                            ((v.zone.y - v.lc[i].c.y) - (v.lc[i].l) / 2)*100);
      rectangle.setOutlineColor(sf::Color::Black);
      rectangle.setOutlineThickness(4) ; 
      window.draw(rectangle);
      i++;
    }; 

    // dessine les personnes
    i=0 ; 
    while ( i < v.lp.size()) {
      sf::CircleShape personne(10) ; 
      personne.setFillColor(sf::Color(0,0,200,150)) ;
      personne.setPosition((v.lp[i].c.x)*100-10  ,
                            (v.zone.y - v.lp[i].c.y)*100-10);
      window.draw(personne); 
      i++ ;

    };

    // dessine le com solution 
    sf::RectangleShape rectangle(sf::Vector2f(com.l*100, com.l*100)) ; 
    rectangle.setFillColor(sf::Color(255, 255, 255, 150  ));
    rectangle.setPosition((com.c.x - (com.l) / 2 )*100,
                            ((v.zone.y - com.c.y) - (com.l) / 2)*100); 
    rectangle.setOutlineColor(sf::Color::Red);
    rectangle.setOutlineThickness(4) ; 
    window.draw(rectangle);
    // end the current frame
    window.display();
  }
};
