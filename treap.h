//
//  treap.h
//  Algoritmen II
//
//  Created by Jonas Anseeuw on 25/12/13.
//  Copyright (c) 2013 Jonas Anseeuw. All rights reserved.
//

#ifndef Algoritmen_II_treap_h
#define Algoritmen_II_treap_h

#include <cstdlib>
#include <iostream>
#include <queue>
#include <deque>
#include "binboom.h"
using std::ostream;


/**********************************************************************
 
 klasse: Treap
 
 beschrijving: Dit is een wrapper voor een Binboom,
 die ervoor zorgt dat de sleutels in de Binboom
 op volgorde staan
 
 ***************************************************************************/

template <class Sleutel,class Data>
class Treap{
public:
	Treap(){
		srand(time(NULL));
	}
	virtual void voegtoe(const Sleutel&);
	//volgende functie doet niets als er geen knoop is met het gegeven Sleutel
	virtual void verwijder(const Sleutel&);
	friend ostream& operator<<(ostream& os,Treap<Sleutel,Data>& b){
        b.deBinboom.schrijf(os);
        return os;
    };
protected:
	// recusieve hulpmethode voor toevoegen
	virtual void voegtoe(Binboom<Sleutel,Data>&h, const Sleutel&);
	//De binaire boom die de data bevat
	Binboom<Sleutel,Data> deBinboom;
};



template <class Sleutel,class Data>
void Treap<Sleutel,Data>::voegtoe(const Sleutel& sl){
    voegtoe(this->deBinboom, sl);
}

template <class Sleutel,class Data>
void Treap<Sleutel,Data>::voegtoe(Binboom<Sleutel,Data>& h, const Sleutel& sl){
	if(h.k == 0){
		int priority = rand()%100;
		h.k = new Binknoop<int, int>(sl,priority);
		return;
	}
	if(sl < h.k->sl){
		voegtoe(h.k->links, sl);
		if(h.k->data < h.k->links.k->data)
			h.roteer(false);
	}else{
		voegtoe(h.k->rechts, sl);
		if(h.k->data < h.k->rechts.k->data)
			h.roteer(true);
	}
	
}

template <class Sleutel,class Data>
void Treap<Sleutel,Data>::verwijder(const Sleutel& sl){
	Binboom<Sleutel,Data>* h = &(this->deBinboom);
	while(h->k != 0 && h->k->sl != sl){
		if(sl < h->k->sl){
			h = &(h->k->links);
		}else{
			h = &(h->k->rechts);
		}
	}
	if(h->k == 0) return;
	
	// Naar beneden roteren
	while(h->k->links.k != 0 || h->k->rechts.k != 0){
		int prio=-1;
		bool naarLinks = true;
		if(h->k->links.k != 0){
			prio = h->k->links.k->data;
			naarLinks = false;
		}
		if(h->k->rechts.k != 0 && h->k->rechts.k->data > prio){
			naarLinks = true;
		}
		
		if(naarLinks){
			h->roteer(true);
			h = &(h->k->links);
		}else{
			h->roteer(false);
			h = &(h->k->rechts);
		}
	}
	
	Binknoop<Sleutel, Data> *magweg = h->k;
	h->k=0;
	delete magweg;
}


#endif
