#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

enum enQuestionLevel{Easy = 1, Medium = 2 , Hard = 3 , Mix = 4};

enum enOperationType{Add = 1 , Sub = 2 , Mul = 3 , Div = 4 , OpMix = 5};

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;

	return randNum;
}

short ReadHowManyQuestions()
{
	short HowManyQuestions = 1;

	do
	{

		cout << "Enter How Many Questions You Want ? ";
		cin >> HowManyQuestions;

	} while (HowManyQuestions < 1 || HowManyQuestions > 10);

	return HowManyQuestions;
}

enQuestionLevel ReadQuestionLevel()
{
	short QuestionLevel = 1;

	do
	{

		cout << "Enter Question Level Choice: [1]: Easy , [2]: Medium, [3]: Hard, [4]: Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
	short OpType = 1;

	do
	{

		cout << "Enter Operation Type: [1]: Add , [2]: Sub, [3]: Mul, [4]: Div, [5]: Mix ? ";
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);

	return (enOperationType)OpType;
}

struct stQuestion
{
	short Number1 = 0;
	short Number2 = 0;
	enQuestionLevel QuestionLevel;
	enOperationType QuestionOperationType;
	short PlayerAnswer = 0;
	short CorrectAnswer = 0;
	short QuestionNumber = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionsList[100];
	short NumberOfQuestions = 0;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	enQuestionLevel QuizzQuestionLevel;
	enOperationType QuizzOperationType;
	bool IsPass = false;

};

enOperationType GetRandomOperationType()
{
	short Op = RandomNumber(1, 4);

	return (enOperationType)Op;
}

short SimpleCalculator(short Number1, short Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mul:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel , enOperationType OpType)
{
	stQuestion Question;

	if (QuestionLevel == enQuestionLevel::Mix)
	{
		QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::OpMix)
	{
		OpType = (enOperationType)GetRandomOperationType();
	}

	Question.QuestionOperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionLevel::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.QuestionOperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::Medium:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.QuestionOperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;

	case enQuestionLevel::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.QuestionOperationType);
		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	
}

void GenerateQuestions(stQuizz &Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionsList[Question] = GenerateQuestion(Quizz.QuizzQuestionLevel, Quizz.QuizzOperationType);
	}
}

string GetOperationTypeString(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mul:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}

void PrintTheQuestion(stQuizz Quizz, short QuestionNumber)
{
	cout << "\nQuestion [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]" << endl << endl;
	cout << Quizz.QuestionsList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionsList[QuestionNumber].Number2 << " ";
	cout << GetOperationTypeString(Quizz.QuestionsList[QuestionNumber].QuestionOperationType) << endl << endl;
	cout << "________________________\n";
}

short ReadPlayerAnswer()
{
	short Answer = 0;
	cin >> Answer;
	return Answer;
}

void SetScreenColor(bool IsPass)
{
	if (IsPass)
		system("color 2F");
	else
		system("color 4F");
}

void CorrectAnswer(stQuizz &Quizz , short QuestionNumber)
{
	if (Quizz.QuestionsList[QuestionNumber].CorrectAnswer != Quizz.QuestionsList[QuestionNumber].PlayerAnswer)
	{
		cout << "Wrong Answer :-(\n";
		cout << "The right answer is: " << Quizz.QuestionsList[QuestionNumber].CorrectAnswer;
		Quizz.NumberOfWrongAnswers++;
		Quizz.QuestionsList[QuestionNumber].AnswerResult = false;
	}
	else
	{
		cout << "Right Answer :-)\n";
		Quizz.NumberOfRightAnswers++;
		Quizz.QuestionsList[QuestionNumber].AnswerResult = true;
	}

	SetScreenColor(Quizz.QuestionsList[QuestionNumber].AnswerResult);
}

void AskAndCorrectAnswer(stQuizz &Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionsList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();

		CorrectAnswer(Quizz, QuestionNumber);
	}

	Quizz.IsPass = (Quizz.NumberOfRightAnswers > Quizz.NumberOfWrongAnswers);
}

string GetPassOrFailString(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "FAIL :-(";
}

string GetQuestionLevelString(enQuestionLevel QuestionLevel)
{
	string arrQuestionLevel[4] = { "Easy", "Medium", "Hard", "Mix" };
	return arrQuestionLevel[QuestionLevel - 1];
}

void PrintGameResults(stQuizz Quizz)
{
	cout << "\n\n_______________________________________________\n\n";
	cout << " Final Results Is " << GetPassOrFailString(Quizz.IsPass);
	cout << "\n\n_______________________________________________\n\n";
	cout << "Number Of Questions     : " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level          : " << GetQuestionLevelString(Quizz.QuizzQuestionLevel) << endl;
	cout << "Operation Type          : " << GetOperationTypeString(Quizz.QuizzOperationType) << endl;
	cout << "Number Of Right Answers : " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answers : " << Quizz.NumberOfWrongAnswers << endl;
	cout << "\n\n________________________________________________\n\n";

	SetScreenColor(Quizz.IsPass);

}

void PlayMathGame()
{
	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuizzQuestionLevel = ReadQuestionLevel();
	Quizz.QuizzOperationType = ReadOperationType();

	GenerateQuestions(Quizz);
	AskAndCorrectAnswer(Quizz);
	PrintGameResults(Quizz);

}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		PlayMathGame();

		cout << "Do you want to play agian [Y/N] ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();

	return 0;
}