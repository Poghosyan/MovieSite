#ifndef MAINWIN_H
#define MAINWIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QGroupBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QFrame>
#include <list>
#include <string>

class MainWin : public QMainWindow
{
	Q_OBJECT

	public:
		MainWin(QWidget *parent = 0);
		~MainWin();

	private slots:
		void checkUsername();
		void createUser();
		void addUser();
		void findByTitle();
		void findByKeyword();
		void addTOQ();
		void removeFromQ();
		void returnToUser();
		void returnMovie();
		
	private:
		//Login Menu
		QLabel		* label;
		QLineEdit	* login;
		QPushButton	* btnNew;
		QPushButton	* btnSubmit;
		QVBoxLayout	* pageLayout;
		QHBoxLayout	* upperItems;
		QHBoxLayout	* lowerButtons;
		QWidget		* loginMenu;

		//Create User menu
		QLabel		* userLogin;
		QLabel		* userName;
		QLineEdit	* loginLineEdit;
		QLineEdit	* nameLineEdit;
		QPushButton	* btnCreate;
		QPushButton * btnCancel;
		QFormLayout * userCreatePrompt;
		QWidget		* createMenu;

		//Logged in menu
		QLabel		* title;
		QLabel		* queueHead;
		QLineEdit	* searchBox;
		QPushButton	* btnLogout;
		QPushButton	* btnReturn;
		QPushButton * btnRent; 
		QPushButton * btnPop;
		QPushButton * btnMoveBack;
		QPushButton * btnByTitle;
		QPushButton	* btnByKeyword;
		QGroupBox	* currentMovie;
		QGroupBox	* movieQueue;
		QGroupBox	* searchMovie;
		QVBoxLayout	* currentMovieLayout;
		QVBoxLayout * queueLayout;
		QHBoxLayout * queueButtons;
		QVBoxLayout * searchLayout;
		QHBoxLayout * searchButtons;
		QVBoxLayout	* overallLoggedLayout;
		QWidget		* loggedMenu;

		//Movie search display
		QLabel		* movieTitle;
		QPushButton	* btnNextMovie;
		QPushButton * btnAddToQ;
		QPushButton * btnRtrnMain;
		QGroupBox	* movieInfo;
		QVBoxLayout	* keywordLayout;
		QVBoxLayout	* movieDisplayLayout;
		QHBoxLayout * movDisplayButtons;
		QWidget		* displayMovie;
		std::list<QLabel *> keywords;
};

#endif