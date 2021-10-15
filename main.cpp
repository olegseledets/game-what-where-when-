#include <iostream>
#include <fstream>

void newPosition(const int &num, int &position);
bool showQuestion(const int &pos);
int getAnswer(const std::string &ans, const int &pos);

int sector[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

int main() {
  int viewersScore = 0, playerScore = 0, currentPosition = 0;

  while(viewersScore != 6 && playerScore != 6){
    int number;
    do {
      std::cout << "Please enter a number: ";
      std::cin >> number;
      if(number <= 0) 
        std::cout << "WARNING: number must be greater than zero." << std::endl;
    } while(number <= 0);
    
    number %= 13;
    newPosition(number, currentPosition);

    if (showQuestion(currentPosition)) {
      std::string myAnsver;
      std::cout << "Please enter your answer: ";
      std::cin >> myAnsver;

      int result;
      result = getAnswer(myAnsver, currentPosition);
      (result) ? ++playerScore : ++viewersScore;
    }
      std::cout << "\ncurrent score: \nPlayer: " << playerScore << "\n" << "Viewer: " << viewersScore << "\n\n";
  }

  std::cout << (playerScore > viewersScore ? "Player wins." : "Viewer wins.") << std::endl;

  return 0;
}

void newPosition(const int &num, int &position){
    position = (position + num) % 13;
    while(sector[position] == -1){
      position = (position + 1) % 13;
    }
    sector[position] = -1;
}

bool showQuestion (const int &pos) {
  std::string fileName = "Tasks/" + std::to_string(pos+1) + "/question.txt";
  std::ifstream question;
  question.open(fileName.c_str(), std::ios::binary);
  if (question.is_open()) {
    std::string line;
    while (getline(question, line)) {
      std::cout << line << std::endl;
    }
    question.close();
  } else {
    std::cout << "This file cannot be opened." << std::endl;
    return 0;
  }
  return 1;
}

int getAnswer(const std::string &ans, const int &pos){
    std::string fileName = "Tasks/" + std::to_string(pos+1) + "/answer.txt";
    std::ifstream answerIn;
    answerIn.open(fileName.c_str(), std::ios::binary);
    std::string answer;
    if (answerIn.is_open()) {        
      answerIn >> answer;
      answerIn.close();
    } else {
      std::cout << "This file cannot be opened." << std::endl;
      return -1;
    }

    if(answer == ans) {
      std::cout << "Player won" << std::endl;
      return 1;
    } else {
      std::cout << "Viewer won" << std::endl;
      return 0;
    }
}

/*
Реализуйте простую версию интеллектуальной игры «Что? Где? Когда?». 

Как происходит игра
В начале каждого хода игроки вращают волчок, то есть выбирают сектор на столе, который сейчас играет. 
Всего таких секторов 13. Сектор выбирается так: с клавиатуры вводится офсет (смещение) относительно текущего сектора на барабане. 
Исходя из этого офсета вычисляется новый активный сектор, который и будет играть в этом ходе. 
Если выпавший сектор уже играл, выбирает следующий неигравший за ним. В начале всей игры стрелка установлена на первом секторе.

Как только играет какой-то из секторов, с него берётся письмо с вопросом — то есть считывается из файла данного сектора. 
Вопрос показывается на экране.

После того как вопрос показан, от игрока ожидается ответ на него. Игрок вводит этот ответ с помощью стандартного ввода. 
То, что он ввёл, сравнивается с ответом, который хранится во втором файле, ассоциированном с активным сектором. 
Данный файл должен содержать лишь одно слово-ответ.

Если ответ знатока-игрока был правильным, ему начисляется один балл. Если неверен, то балл уходит телезрителям.

Игра продолжается до тех пор, пока или игрок, или зрители не наберут шесть баллов. 
После этого называется победитель и программа заканчивает работу.
*/