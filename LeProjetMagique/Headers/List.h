#pragma once
// <sberube>
#ifndef _LIST_H_
/*
Liste doublement cha�n�e repr�sent�e par des bo�tes
qui pointe sur la suivante et la pr�c�dante.

Utilisation: - Liste d'armes du joueur
- Liste d'ennemies dans le jeu
- Liste des bonus dans le jeu
- Liste des m�t�orites
*/
template <class T>
class List
{
private:
	// Bo�te
	struct Box
	{
		T value;
		Box* next;
		Box* previous;
		Box(const T& value = T(), Box* next = nullptr, Box* prev = nullptr) :value(value), next(next), previous(prev) {}
		~Box() { previous = next = nullptr; }
	};

	//List(const List&) = delete;

	//Representation
	Box before, after;
	size_t sz;

	//fonctions generatrices privees
	//boite* insert(boite*, const TYPE&); //inserer avant cette boite  ++++++++++++++
	//boite* erase(boite*); //enlever cette boite                      ++++++++++++++
public:

	// Foward declaration
	class Iterator;

	//Constructeur et affectateur
	List();
	~List();
	List& operator=(const List<T>& other);

	//Accesseur
	T& Front();
	T& Back();
	const T& Front() const;
	const T& Back() const;

	Iterator Start() { return Iterator(before.next); }
	Iterator End() {return Iterator(after.previous);}


	//Capacite
	bool Empty() const;
	size_t Size() const;

	//Fonction generatrice
	void PushFront(const T& value);
	void PushBack(const T& value);
	void PopFront();
	void PopBack();
	void Swap(List& other) noexcept;
};

template<class T>
inline List<T>::List() : sz(0)
{
	before.previous = nullptr;
	after.next = nullptr;
}

template<class T>
inline List<T>::~List()
{
	// On vide la list
	while (sz > 0)
	{
		PopFront();
	}
}

template<class T>
inline List<T>& List<T>::operator=(const List<T>& other)
{
	// l'index pour parcourir la chaine.
	Box *index = other.before.next;

	// On vide la cha�ne
	while (sz > 0)
	{
		PopFront();
	}

	// On copie chaque �l�ments de other a this.
	for (size_t i = 0; i < other.sz; i++)
	{
		this->PushFront(index->value);
		index = index->next;
	}

	return *this;
}

template<class T>
inline T & List<T>::Front()
{
	return before.next->value;
}

template<class T>
inline T & List<T>::Back()
{
	return after.previous->value;
}

template<class T>
inline const T & List<T>::Front() const
{
		return before.next->value;
}

template<class T>
inline const T & List<T>::Back() const
{
	return after.previous->value;
}

template<class T>
inline bool List<T>::Empty() const
{
	return sz == 0;
}

template<class T>
inline size_t List<T>::Size() const
{
	return sz;
}

template<class T>
inline void List<T>::PushFront(const T& value)
{
	// Si la taille est de 0...
	if (sz == 0)
	{
		// Cr�ation d'une premi�re nouvelle bo�te.
		Box *first = new Box();
		first->next = after;
		first->previous = &before;

		before.next = first;
		after.previous = first;

		// On positionne l'itt�rateur sur l'�l�ment 0.
		iterator.currIndex = first->next;
	}
	else
	{
		// Cr�ation d'une nouvelle bo�te.
		Box *box = new Box();

		// On positionne cette-ci entre le d�but et la premi�re bo�te.
		box->previous = before;
		box->next = before.next;

		before.next->previous = box;
		before.next = box;
	}
	// Il y a un �l�ment de plus
	sz++;
}

template<class T>
inline void List<T>::PushBack(const T& value)
{
	// Si la taille est de 0...
	if (sz == 0)
	{
		// Cr�ation d'une premi�re nouvelle bo�te.
		Box *first = new Box();
		first->next = &after;
		first->previous = &before;

		before.next = first;
		after.previous = first;

	}
	else
	{
		// Cr�ation d'une nouvelle bo�te.
		Box *box = new Box();

		// On positionne cette-ci entre la fin et la derni�re bo�te.
		box->previous = after.previous;
		box->next = &after;

		after.previous->next = box;
		after.previous = box;
	}
	// Il y a un �l�ment de plus
	sz++;
}

template<class T>
inline void List<T>::PopFront()
{
	// Si il y a au moins un �l�ment...
	if (sz > 0)
	{
		// On pointe sur le premier �l�ment
		Box *popBox = before.next;
		
		// On l'enl�ve de la cha�ne.
		before.next = popBox->next;
		popBox->next->previous = &before;

		// On le supprime
		delete popBox;
		popBox = nullptr;

		// La taille est r�duite
		sz--;
	}
}

template<class T>
inline void List<T>::PopBack()
{
	if (sz > 0)
	{
		// On pointe sur le dernier �l�ment
		Box *popBox = after.previous;

		// On l'enl�ve de la cha�ne.
		after.previous = popBox->previous;
		popBox->previous->next = after;

		// On le supprime
		delete popBox;
		popBox = nullptr;

		// La taille est r�duite
		sz--;
	}
}

template<class T>
inline void List<T>::Swap(List& other) noexcept
{
	// valeurs temporaires pour la permutation.
	Box *first = before.next;
	Box *last = after.previous;

	// On �change le premier et le dernier �l�ment.
	before.next = other.before.next;
	after.previous = other.after.previous;

	other.before.next = first;
	other.after.prev = last;
}


///////////////////////////////////////////////////////////
//la classe iterator
///////////////////////////////////////////////////////////

template <class T>
class List<T>::Iterator {
	friend class List<T>;
private:

	Box* currIndex;

public:

	Iterator(Box*c = nullptr) : currIndex(c) {}

	T& operator*()const //Dereference l'iterateur
	{
		return currIndex->value;
	}

	T* operator->()const { return &(currIndex->value); } //Autre dereference

	Iterator& operator++() //++i
	{
		currIndex = currIndex->next; // boite suivante
		return *this;
	}

	Iterator operator++(int) {   //i++
		currIndex = currIndex->next; // boite suivante
		return *this;
	}

	Iterator& operator--() //--i
	{
		currIndex = currIndex->previous; // boite pr�c�dente
		return *this;
	}
	Iterator operator--(int) {   //i--
		currIndex = currIndex->previous; // boite pr�c�dente
		return *this;
	}
	bool operator==(const Iterator &droite)const { // comparaison d'iterateur
		return currIndex == droite.currIndex;
	}
	bool operator!=(const Iterator &droite)const { // comparaison d'iterateur
		return currIndex != droite.currIndex;
	}
};
#endif // !__LIST_H_
// </sberube>