#include "SimpleButton.hpp"
#include "Conf.hpp"
#include "Gestures.hpp"
#include "log.hpp"
#include "Lang.hpp"

void SimpleButton::update(sf::RenderWindow &rw){
	if(visible && enabled){
		if(hover){
			lmsg.changes.clear();
			lmsg.changes[S::state_hover]=S::one;

			if(Gestures::get()==Gestures::FastTap){
				Gestures::lock();
				clickSound.stop();
				clicked = true;
				clickSound.setVolume(Conf::menuSoundVolume);
				clickSound.play();

				lmsg.changes[S::state_clicked]=S::one;
			}
			notifyListeners();
		}
		else clicked = false;

		checkHover(rw, computedPosition(rw, size));
	}else{
		clicked=false;
		hover=false;
	}
}
void SimpleButton::draw(sf::RenderTarget &target, sf::RenderStates states)const{
	if(visible){
		sf::Text t;
		sf::RectangleShape s;

		t.setFont(Conf::fSansation);
		t.setCharacterSize(textSize*Conf::gs);

		if(textParse){
			t.setString(l(text));
		}else{
			t.setString(s2ws(text));
		}

		s.setTexture(texture);
		s.setSize(size*Conf::gs);
		s.setOutlineColor(sf::Color::Transparent);
		s.setOutlineThickness(0.0f);
		s.setScale(Conf::zm, Conf::zm);

		sf::Vector2f computed=computedPosition(target, size);
		s.setPosition(computed);


		if(hover){
			s.setFillColor(sf::Color::White);
		}else{
			s.setFillColor(sf::Color(128,128,128));
		}

		t.setOutlineColor(textOutlineColor);
		t.setOutlineThickness(textOutlineSize*Conf::gs);
		if(!enabled){
			s.setFillColor(sf::Color(100,100,100,220));
			t.setFillColor(textColor*sf::Color(220,220,220,220));
		}else{
			t.setFillColor(textColor);
		}

		t.setPosition(s.getPosition()+textShift*Conf::gs*Conf::zm);
		t.setScale(Conf::zm, Conf::zm);


		sf::FloatRect fr;
		fr.width=s.getGlobalBounds().width - 2*textShift.x*Conf::gs*Conf::zm;
		fr.height=s.getGlobalBounds().height - 2*textShift.y*Conf::gs*Conf::zm;


		if(textCenter){
			sf::Text test=t;
			test.setString("ÓTyjqĘ");

			float h=test.getGlobalBounds().height;
			float tmp;
			if((tmp=t.getGlobalBounds().height)>h) h=tmp;


			t.move( (s.getGlobalBounds().width - t.getGlobalBounds().width)/2 , (s.getGlobalBounds().height - h)/2.33);
		}else{
			formatText(t,fr);
		}

		sf::RectangleShape img;

		if(imageTex != NULL){
			img.setTexture(imageTex);
			img.setTextureRect(imageTexRect);

			float ratio;

			if(imageTexRect.height > imageTexRect.width){
				ratio=s.getGlobalBounds().height/imageTexRect.height;
			}else{
				ratio=s.getGlobalBounds().width/imageTexRect.width;
			}
			img.setSize(sf::Vector2f(ratio*imageTexRect.width * imageScale, ratio*imageTexRect.height * imageScale));

			sf::Vector2f p=s.getPosition();
			p.y+=(s.getGlobalBounds().height - img.getGlobalBounds().height)/2;
			p.x+=(s.getGlobalBounds().width - img.getGlobalBounds().width)/2;
			img.setPosition(p);

			//img.move(sf::Vector2f((s.getGlobalBounds().width-img.getGlobalBounds().width)/2, 0.0f));
		}

		target.draw(s, states);
		if(imageTex != NULL) target.draw(img, states);
		target.draw(t ,states);

	}
}
void SimpleButton::setImageTextureRect(sf::IntRect ir){
	imageTexRectAbsolute=ir;
	imageTexRect = Conf::irCorrection(ir);
}
