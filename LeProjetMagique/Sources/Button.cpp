#include "Button.h"

using namespace spaceShooter;

Button::Button()
{
}

Button::~Button()
{
}

/// <summary>
/// Initiation d'un Textbox.  Le choix ne rien mettre dans le constructeur vient du fait
/// Qu'il est inutile d'initialiser quoi que ce soit tant qu'on a pas une font valide.
/// O� alors on serait oblig� de l'utiliser comme pointeur.
/// La m�thode init r�gle la question
///
/// Certains �l�ments sont d�lib�r�ments hardcod�s; on ne veut pas une textbox hyper-flexible
/// Juste de quoi qui fera le travail pour ce TP
///
/// </summary>
/// <param name="longueur">Longueur du Textbox</param>
/// <param name="limite">Limite de caract�res; devrait �tre 1 pour 20 pixels de longueur du textbox</param>
/// <param name="position">Position � l'�cran.  Le Textbox est centr�e sur cette position.</param>
/// <param name="font">La font utilis�e</param>
void Button::init(const int longueur, const int limite, const Vector2f position, const Font& font)
{
    int hauteur = 30;
    this->limite = limite;

    boite.setSize(Vector2f(longueur, hauteur));
    boite.setFillColor(Color::Black);
    boite.setOutlineColor(Color::White);
    boite.setOutlineThickness(2);
    boite.setOrigin(Vector2f(longueur / 2, hauteur / 2));
    boite.setPosition(position);

    texte.setFont(font);
    texte.setCharacterSize(20);
    texte.setFillColor(Color::White);

    //Backup des dimensions pour un �ventuel setSize
    lastWidth = longueur;
    lastHeight = hauteur;
}


/// <summary>
/// Voir pr�c�dent, mais utilis� comme Label
/// La boite est toujours pr�sente (pas le choix), mais carr�ment invisible
///
/// Si le texte notifie une erreur, on le mettra de couleur rouge
/// </summary>
void Button::initInfo(const Vector2f position, const Font& font, const bool estErreur)
{
    int hauteur = 30;
    this->limite = 60;// pas de graphique associ�, on peut mettre un long texte par d�faut.

    boite.setSize(Vector2f(0, 0));
    boite.setFillColor(Color::Transparent);
    boite.setOutlineColor(Color::Transparent);
    boite.setOutlineThickness(0);
    boite.setOrigin(Vector2f(0, 0));
    boite.setPosition(position);

    texte.setFont(font);
    texte.setCharacterSize(20);

    if (estErreur)
    {
        texte.setFillColor(Color::Red);
    }
    else
    {
        texte.setFillColor(Color::White);
    }
}

/// <summary>
/// Fait juste changer la couleur du cadre.
/// </summary>
void Button::selectionner(Color color)
{
    boite.setOutlineColor(color);
}

void Button::deSelectionner()
{
    boite.setOutlineColor(Color::White);
}

/// <summary>
/// V�rifie si une position touche au textbox
/// </summary>
bool Button::touche(const Vector2i& position)
{
    FloatRect coord = boite.getGlobalBounds();

    if (position.x > coord.left && position.x < coord.left + coord.width &&
        position.y > coord.top && position.y < coord.top + coord.height)
    {
        return true;
    }

    return false;
}

void spaceShooter::Button::SetFontColor(Color color)
{
    texte.setFillColor(color);
}

float Button::getTailleTexte()
{
    return texte.getCharacterSize();
}

void spaceShooter::Button::SetSize(int longueur, int hauteur)
{
    //<smasson>
    //Initialisation des variables
    int totalLast = lastWidth + lastHeight;
    int totalNew = longueur + hauteur;
    float percent = totalNew / totalLast;
    bool isHigher = totalNew > totalLast;
    int newFontSize = texte.getCharacterSize();
    //Si nous avons une taille moyennement plus grande que la pr�c�dente
    if (isHigher)
    {
        //On agrandit la size de la font
        percent = percent - 1;
        newFontSize = texte.getCharacterSize()*percent + texte.getCharacterSize();
    }
    //Sinon, si nous avons une size moyennement plus petite que la pr�c�dente
    else if (totalNew != totalLast)
    {
        //On r�duit la size de la font
        newFontSize = texte.getCharacterSize() - texte.getCharacterSize()*percent;
    }
    //Appliquer les changements
    texte.setCharacterSize(newFontSize);
    boite.setSize(Vector2f(longueur, hauteur));
    boite.setOrigin(Vector2f(longueur / 2, hauteur / 2));
    //</smasson>
}

String Button::getTexte() const
{
    return texte.getString();
}

/// <summary>
/// Le texte est ins�r� et remplace le pr�c�dent.
/// </summary>
/// <param name="leTexte">The le texte.</param>
void Button::insererTexte(String leTexte)
{
    //Si trop long on concat�ne
    if (leTexte.getSize() > limite)
    {
        leTexte = leTexte.substring(0, limite);
    }

    texte.setString(leTexte);
    ajustementsVisuels();
}
/// <summary>
/// On ajoute un caract�re � la string, si on est pas � la longueur maximale
/// </summary>
void Button::ajouterChar(const char leChar)
{
    if (texte.getString().getSize() >= limite) return;

    texte.setString(texte.getString() + leChar);
    ajustementsVisuels();
}

/// <summary>
/// On retire un caract�re � la string, si on est pas � la longueur 0
/// </summary>
void Button::retirerChar()
{
    if (texte.getString().getSize() == 0) return;

    texte.setString(texte.getString().substring(0, texte.getString().getSize() - 1));
    ajustementsVisuels();
}

/// <summary>
/// Ajustements visuels: le texte est toujours centr� sur la position de la boite.
/// </summary>
void Button::ajustementsVisuels()
{
    FloatRect coord = texte.getGlobalBounds();
    texte.setOrigin(Vector2f(coord.width / 2, coord.height / 2));
    texte.setPosition(boite.getPosition().x, boite.getPosition().y - (texte.getCharacterSize() / 10 * 2 + 1)/*-5*/);
}

void Button::dessiner(RenderWindow* const window)
{
    window->draw(boite);
    window->draw(texte);
}
