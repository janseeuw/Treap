//
//  binboom.h
//  Algoritmen II
//
//  Created by Jonas Anseeuw on 25/12/13.
//  Copyright (c) 2013 Jonas Anseeuw. All rights reserved.
//

#ifndef Algoritmen_II_binboom_h
#define Algoritmen_II_binboom_h

/**********************************************************************
 
 Klasse: Binboom met Binknoop: binaire boom
 
 beschrijving: Domme klasse om de gegevens van een boom te bevatten
 Omdat ze enkel in een wrapper wordt gebruikt, heeft ze
 alles publiek staan. Ze mag dan ook nooit buiten een
 wrapper gebruikt worden!
 
 ***************************************************************************/

template <class Sleutel,class Data>
class Binknoop;

template <class Sleutel,class Data>
class Binboom{
public:
    Binboom<Sleutel,Data>():k(0){}
	~Binboom<Sleutel,Data>(){
        delete k;
    }
	int diepte() const{
        if (k==0)
            return 0;
        else
            return std::max(k->links.diepte(),k->rechts.diepte())+1;
    }
	void schrijf(std::ostream&) const;
	void schrijf(std::ostream& os,Binknoop<Sleutel,Data>* kn) const{
        if (kn!=0)
            os<<"("<<kn->sl<<","<<kn->data<<")";
        else
            os<<"(,)";
    }
	void roteer(bool links);
	//pointer naar wortelknoop
	Binknoop<Sleutel,Data>* k;
};

template <class Sleutel,class Data>
class Binknoop{
public:
	Sleutel sl;
	Data data;
	Binknoop<Sleutel,Data>* ouder;
	Binboom<Sleutel,Data> links,rechts;
	Binknoop():ouder(0){}
	Binknoop(const Sleutel& _sl,const Data& _data):ouder(0),sl(_sl),data(_data){}
};

template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::roteer(bool links){
    Binknoop<Sleutel,Data>* op;
    Binknoop<Sleutel,Data>* neer=k;
    if (links){
        op=k->rechts.k;
        neer->rechts.k=op->links.k;
        op->links.k=neer;
        if (neer->rechts.k!=0)
            neer->rechts.k->ouder=neer;
    }
    else{
        op=k->links.k;
        neer->links.k=op->rechts.k;
        op->rechts.k=neer;
        if (neer->links.k!=0)
            neer->links.k->ouder=neer;
    }
    k=op;
    op->ouder=neer->ouder;
    neer->ouder=op;
	neer=0;
	op=0;
}


template <class Sleutel,class Data>
void Binboom<Sleutel,Data>::schrijf(std::ostream& os) const{
    if (k!=0){
		std::queue<Binknoop<Sleutel,Data>*, std::deque<Binknoop<Sleutel,Data>*> > q;
		q.push(k);
		while(!q.empty()){
			Binknoop<Sleutel,Data>* nu=q.front();
			schrijf(os,nu);
			os<<" links: ";
			schrijf(os,nu->links.k);
			os<<" rechts: ";
			schrijf(os,nu->rechts.k);
			os<<" ouder: ";
			schrijf(os,nu->ouder);
			os<<std::endl;
			if (nu->links.k!=0)
				q.push(nu->links.k);
			if (nu->rechts.k!=0)
				q.push(nu->rechts.k);
			q.pop();
		}
    }
    else{
        schrijf(os,k);
    }
}

#endif
