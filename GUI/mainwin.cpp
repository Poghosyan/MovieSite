#include "mainwin.h"
#include <QCloseEvent>
#include <QCDEStyle>
#include <QWindowsStyle>

MainWin::MainWin (QWidget *parent) : QMainWindow(parent) {
	//Login Menu
	label			= new QLabel("Login:");
	login 			= new QLineEdit;
	btnNew 			= new QPushButton("New User");
	btnSubmit 		= new QPushButton("Submit");
	pageLayout 		= new QVBoxLayout;
	upperItems		= new QHBoxLayout;
	lowerButtons	= new QHBoxLayout;
	loginMenu 		= new QWidget;

	loginMenu->setLayout(pageLayout);
	this->setCentralWidget(loginMenu);

	label->setBuddy(login);
	pageLayout->addLayout(upperItems, 0);
	pageLayout->addLayout(lowerButtons, 1);
	upperItems->addWidget(label, 0);
	upperItems->addWidget(login, 1);
	lowerButtons->addWidget(btnNew, 0);
	lowerButtons->addWidget(btnSubmit, 1);

	//Create User
	userLogin		= new QLabel("Login:");
	userName		= new QLabel("Name:");
	loginLineEdit	= new QLineEdit;
	nameLineEdit	= new QLineEdit; 
	btnCreate		= new QPushButton("Create");
	btnCancel		= new QPushButton("Cancel");
	userCreatePrompt= new QFormLayout;
	createMenu		= new QWidget;

	//createMenu->setFrameStyle(QFrame::Panel | QFrame::Raised);
	createMenu->setLayout(userCreatePrompt);

	userCreatePrompt->addRow(userLogin, loginLineEdit);
	userCreatePrompt->addRow(userName, nameLineEdit);
	userCreatePrompt->addRow(btnCreate, btnCancel);

	//Logged Menu
	QStyle * style 		= new QWindowsStyle;
	title 				= new QLabel("things in here");
	queueHead			= new QLabel("Ttiele");
	searchBox			= new QLineEdit;
	btnLogout			= new QPushButton("Logout");
	btnReturn			= new QPushButton("Return Movie");
	btnRent				= new QPushButton("Rent Movie");
	btnPop				= new QPushButton("Delete from Queue");
	btnMoveBack			= new QPushButton("Move to back of Queue");
	btnByTitle			= new QPushButton("Search by Title");
	btnByKeyword		= new QPushButton("Search by Keyword");
	currentMovie 		= new QGroupBox("Current Movie");
	movieQueue	 		= new QGroupBox("Movie Queue");
	searchMovie 		= new QGroupBox("Search For Movie");
	currentMovieLayout	= new QVBoxLayout;
	queueLayout 		= new QVBoxLayout;
	queueButtons		= new QHBoxLayout;
	searchLayout		= new QVBoxLayout;
	searchButtons		= new QHBoxLayout;
	overallLoggedLayout	= new QVBoxLayout;
	loggedMenu			= new QWidget;

	//Logged menu current movie
	currentMovieLayout->addWidget(title, 0);
	currentMovieLayout->addWidget(btnReturn, 1);
	currentMovie->setStyle(style);
	currentMovie->setLayout(currentMovieLayout);
	
	//logged menu Movie queue
	queueLayout->addWidget(queueHead);
	queueButtons->addWidget(btnRent, 0);
	queueButtons->addWidget(btnPop, 1);
	queueButtons->addWidget(btnMoveBack, 2);		
	queueLayout->addLayout(queueButtons, 1);	
	movieQueue->setStyle(style);
	movieQueue->setLayout(queueLayout);

	//Logged menu search
	searchLayout->addWidget(searchBox);
	searchButtons->addWidget(btnByTitle, 0);
	searchButtons->addWidget(btnByKeyword, 1);
	searchLayout->addLayout(searchButtons, 1);
	searchMovie->setStyle(style);
	searchMovie->setLayout(searchLayout);

	overallLoggedLayout->addWidget(currentMovie, 0);
	overallLoggedLayout->addWidget(movieQueue, 1);
	overallLoggedLayout->addWidget(searchMovie, 2);
	overallLoggedLayout->addWidget(btnLogout, 3);
	loggedMenu->setLayout(overallLoggedLayout);

	//Moive Info Display
	movieTitle			= new QLabel();
	btnNextMovie		= new QPushButton("Next Movie");
	btnAddToQ			= new QPushButton("Add to my Queue");
	btnRtrnMain			= new QPushButton("Return to Main Menu");
	movieInfo			= new QGroupBox("Movie Info");
	keywordLayout		= new QVBoxLayout;
	movieDisplayLayout	= new QVBoxLayout;
	movDisplayButtons	= new QHBoxLayout;
	displayMovie		= new QWidget;

	movieInfo->setStyle(style);
	movieDisplayLayout->addWidget(movieTitle, 0);
	movieDisplayLayout->addWidget(movieInfo, 1);
	movieInfo->setLayout(keywordLayout);
	movieDisplayLayout->addLayout(movDisplayButtons);
	movDisplayButtons->addWidget(btnNextMovie, 0);
	movieDisplayLayout->addWidget(btnAddToQ, 1);
	movDisplayButtons->addWidget(btnRtrnMain, 2);
	displayMovie->setLayout(movieDisplayLayout);

	connect(btnSubmit, SIGNAL(clicked()), this, SLOT(checkUsername()));
	connect(btnRtrnMain, SIGNAL(clicked()), this, SLOT(checkUsername()));
	connect(btnNew, SIGNAL(clicked()), this, SLOT(createUser()));
	connect(btnCreate,SIGNAL(clicked()), this,SLOT(addUser()));
	connect(btnByTitle, SIGNAL(clicked()), this, SLOT(findByTitle()));
	connect(btnByKeyword, SIGNAL(clicked()), this, SLOT(findByKeyword()));
	connect(btnLogout, SIGNAL(clicked()), this, SLOT(returnToUser()));
	connect(btnCancel,SIGNAL(clicked()), this,SLOT(returnToUser()));

}

MainWin::~MainWin() {
	delete label;
	delete login;
	delete btnNew;
	delete btnSubmit;
	delete upperItems;
	delete lowerButtons;
	delete pageLayout;
	delete loginMenu;
}

void MainWin::checkUsername() {
	this->setCentralWidget(loggedMenu);
}

void MainWin::createUser() {
	this->setCentralWidget(createMenu);
}

void MainWin::addUser() {

}

void MainWin::findByTitle() {
	this->setCentralWidget(displayMovie);
}

void MainWin::findByKeyword() {
	this->setCentralWidget(displayMovie);
}

void MainWin::addTOQ() {

}

void MainWin::removeFromQ() {

}

void MainWin::returnToUser() {
	this->setCentralWidget(loginMenu);
	loginMenu->show();
}

void MainWin::returnMovie() {

}