#include<iostream>
#include<vector>
using namespace std;

//Parent class...
class QuestionBase {
protected:
    string text;
public:
    QuestionBase(string text) : text(text) {}
    string getText() { return text; }
};

//Child class...
class Question : public QuestionBase {
private:
    string answer;
    vector<string> options;
public:
    Question(string text, string answer, vector<string> options) : QuestionBase(text), answer(answer), options(options) {}
    string getAnswer() { return answer; }
    vector<string> getOptions() { return options; }
};

//Grand child class...
class QuizQuestion : public Question {
private:
    char userChoice;
    bool skipped;
    int attempts;
public:
    QuizQuestion(string text, string answer, vector<string> options) : Question(text, answer, options), skipped(false), attempts(0) {}
    void setUserChoice(char userChoice) { this->userChoice = userChoice; }
    char getUserChoice() { return userChoice; }
    void setSkipped(bool skipped) { this->skipped = skipped; }
    bool isSkipped() { return skipped; }
    void incrementAttempts() { attempts++; }
    int getAttempts() { return attempts; }
};

//Grand grand child class...
class Quiz : public QuizQuestion {
private:
    vector<QuizQuestion> questions;
    string  name, fatherName, gender, dob, cnic;
    int Chances = 3;
    double realPercentage;
public:
    Quiz(string text, string answer, vector<string> options) : QuizQuestion(text, answer, options), realPercentage(0.0) {}
    void addQuestion(QuizQuestion question) { questions.push_back(question); }
    void displayQuestions() {
        int correctCount = 0;
        string Spaces = "\t\t\t\t";
        cout<< "\t    _________________________________________________________________________________________"<<endl;
        cout<< "\t   |  _____________________________________________________________________________________  |"<<endl;
        cout<< "\t   | |                                                                                     | |"<<endl;
        cout<< "\t   | |                      In This Application,You Are Permitted To:                      | |"<<endl;
        cout<< "\t   | |                                                                                     | |"<<endl;
        cout<< "\t   | |                      1. Skip a single question one time only.                       | |"<<endl;
        cout<< "\t   | |                                                                                     | |"<<endl;
        cout<< "\t   | |      2. Select your answer from the options (A-D), regardless of whether they       | |"<<endl;
        cout<< "\t   | |                        are in small or capital case letters.                        | |"<<endl;
        cout<< "\t   | |                                                                                     | |"<<endl;
        cout<< "\t   | |  3. To skip a question, you can simply enter 'N', either in capital or small case.  | |"<<endl;
        cout<< "\t   | |                                                                                     | |"<<endl;
        cout<< "\t   | |                      Remember to make your selection carefully,                     | |"<<endl;
        cout<< "\t   | |                                  good luck and have                                 | |"<<endl;
        cout<< "\t   | |                                     fun playing.                                    | |"<<endl;
        cout<< "\t   | |_____________________________________________________________________________________| |"<<endl;
        cout<< "\t   |_________________________________________________________________________________________|\n\n"<<endl;
        cout << "  Enter your name: ";
        getline(cin, name);
        cout << "  Enter your father's name: ";
        getline(cin, fatherName);
        while(Chances > 0){
            cout << "  Enter your gender (Male/Female): ";
            getline(cin, gender);
            for (char & G : gender){
                G = tolower(G);
            }
            if (gender == "m" || gender == "male"){
                gender = "Male";
                break;
            }else if(gender == "f" || gender == "female"){
                gender = "Female";
                break;
            }else{
                cout << "  Invalid input? Please enter M/F or male/female?"<<endl;
                Chances--;
            }
        }
        if (Chances == 0){
            cout << "  You've exceeded the number of chances?"<<endl;
        }
        cout << "  Enter your date of birth (DD/MM/YYYY): ";
        getline(cin, dob);
        while (Chances > 0 ){
            cout << "  Enter your CNIC number (13-Digits and 2-dashes): ";
            getline(cin, cnic);
            if (cnic.length() == 15){
                break;
            }else{
                cout << "  Invalid input. Please enter a less than or 13 digits number"<<endl;
                Chances--;
            }
        }
        if (Chances == 0){
            cout << "  You've exceeded the number of chances."<<endl;
        }
        system("cls");
        cout<< "\n"<<endl;
        cout<< Spaces<<"   ___________________________________________________"<<endl;
        cout<< Spaces<<"  |  _______________________________________________  |"<<endl;
        cout<< Spaces<<"  | |                                               | |"<<endl;
        cout<< Spaces<<"  | |  Questions Are Given Below Choose One Option  | |"<<endl;
        cout<< Spaces<<"  | |_______________________________________________| |"<<endl;
        cout<< Spaces<<"  |___________________________________________________|\n\n"<<endl;

        vector<int> skippedQuestions;
        for (int i = 0; i < questions.size(); i++) {
            cout << "  Question " << (i + 1) << ": " << questions[i].getText() << endl;
            cout << "  Options:"<<endl;
            vector<string> options = questions[i].getOptions();
            for (int j = 0; j < options.size(); j++) {
                cout <<"\t  "<< (char)('A' + j) << ". " << options[j] << endl;
            }
            cout << "  Enter your choice (A-" << (char)('A' + options.size() - 1) << " or a-" << (char)('a' + options.size() - 1) << "), or 'N' for next question: ";
            char userChoice;
            cin >> userChoice;
            if (userChoice == 'N' || userChoice == 'n') {
                questions[i].setSkipped(true);
                skippedQuestions.push_back(i);
                cout<< "  Skipped"<<endl;
                cout <<"\n-------------------------------------------------------------------------"<<endl;
                cout <<":-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:"<<endl;
                cout <<"-------------------------------------------------------------------------\n"<<endl;
                continue;
            }
            userChoice = toupper(userChoice);
            while (userChoice < 'A' || userChoice > 'A' + options.size() - 1) {
                cout << "  Invalid choice. Please enter a choice between A and " << (char)('A' + options.size() - 1) << " or a-" << (char)('a' + options.size() - 1) << ": ";
                cin >> userChoice;
                if (userChoice == 'N' || userChoice == 'n') {
                    questions[i].setSkipped(true);
                    skippedQuestions.push_back(i);
                    break;
                }
                userChoice = toupper(userChoice);
            }
            if (questions[i].isSkipped()) continue;
            questions[i].setUserChoice(userChoice);
            if (options[userChoice - 'A'] == questions[i].getAnswer()) {
                cout << "  Correct!" << endl;
                correctCount++;
            } else {
                cout << "  Incorrect. The correct answer is " << questions[i].getAnswer() << endl;
            }
            cout << endl;
            cout <<"-------------------------------------------------------------------------"<<endl;
            cout <<":-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:"<<endl;
            cout <<"-------------------------------------------------------------------------\n"<<endl;
        }
        system("cls");
        cout<< "\n"<<endl;
        cout<< Spaces<<"   __________________________________________________"<<endl;
        cout<< Spaces<<"  |  ______________________________________________  |"<<endl;
        cout<< Spaces<<"  | |                                              | |"<<endl;
        cout<< Spaces<<"  | |  Questions That You Skipped Are Given Below  | |"<<endl;
        cout<< Spaces<<"  | |______________________________________________| |"<<endl;
        cout<< Spaces<<"  |__________________________________________________|\n\n"<<endl;
        for (int i = 0; i < skippedQuestions.size(); i++) {
            int questionIndex = skippedQuestions[i];
            cout << "  Question " << (questionIndex + 1) << ": " << questions[questionIndex].getText() << endl;
            vector<string> options = questions[questionIndex].getOptions();
            cout<< "  Options: "<<endl;
            for (int j = 0; j < options.size(); j++) {
                cout <<"\t  "<< (char)('A' + j) << ". " << options[j] << endl;
            }
            cout << "  Enter your choice (A-" << (char)('A' + options.size() - 1) << " or a-" << (char)('a' + options.size() - 1) << "): ";
            char userChoice;
            cin >> userChoice;
            if (userChoice == 'N' || userChoice == 'n') {
                if (questions[questionIndex].getAttempts() > 0) {
                    cout << "  You have already skipped this question. Moving to the next one." << endl;
                    continue;
                } else {
                    questions[questionIndex].setSkipped(true);
                    questions[questionIndex].incrementAttempts();
                    cout << "  SORRY! You are unable to attempt this question because you skipped it for second time?"<<endl;
                    cout <<"\n-------------------------------------------------------------------------"<<endl;
                    cout <<":-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:"<<endl;
                    cout <<"-------------------------------------------------------------------------\n"<<endl;
                    continue;
                }

            }
            userChoice = toupper(userChoice);
            while (userChoice < 'A' || userChoice > 'A' + options.size() - 1) {
                cout << "  Invalid choice. Please enter a choice between A and " << (char)('A' + options.size() - 1) << " or a-" << (char)('a' + options.size() - 1) << ": ";
                cin >> userChoice;
                if (userChoice == 'N' || userChoice == 'n') {
                    if (questions[questionIndex].getAttempts() > 0) {
                        cout << "  You have already skipped this question. Moving to the next one." << endl;
                        break;
                    } else {
                        questions[questionIndex].setSkipped(true);
                        questions[questionIndex].incrementAttempts();
                        break;
                    }

                }
                userChoice = toupper(userChoice);
            }
            questions[questionIndex].setUserChoice(userChoice);
            if (options[userChoice - 'A'] == questions[questionIndex].getAnswer()) {
                cout << "  Correct!" << endl;
                correctCount++;
            } else {
                cout << "  Incorrect. The correct answer is " << questions[questionIndex].getAnswer() << endl;
            }
            cout << endl;
            cout <<"-------------------------------------------------------------------------"<<endl;
            cout <<":-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:-:"<<endl;
            cout <<"-------------------------------------------------------------------------\n"<<endl;
        }
        system("cls");
        cout<< Spaces<<"\t       _______________________"<<endl;
        cout<< Spaces<<"\t      |  ___________________  |"<<endl;
        cout<< Spaces<<"\t      | |                   | |"<<endl;
        cout<< Spaces<<"\t      | |    R E S U L T    | |"<<endl;
        cout<< Spaces<<"\t      | |___________________| |"<<endl;
        cout<< Spaces<<"\t      |_______________________|\n\n"<<endl;

        cout<< Spaces<<"\t       _______________________"<<endl;
        cout<< Spaces<<"\t      |  ___________________  |"<<endl;
        cout<< Spaces<<"\t      | |                   | |"<<endl;
        cout<< Spaces<<"\t      | |   Personal Data   | |"<<endl;
        cout<< Spaces<<"\t      | |___________________| |"<<endl;
        cout<< Spaces<<"\t      |_______________________|\n\n"<<endl;
        for (char &UpperName_1 : name){
            UpperName_1 = toupper(UpperName_1);
        }
        cout << "  Name:          " << name << endl;
        for (char &UpperName_2 : fatherName){
            UpperName_2 = toupper(UpperName_2);
        }
        cout << "  Father's Name: " << fatherName << endl;
        cout << "  Gender:        " << gender << endl;
        for (size_t i = 0; i <dob.length(); i++){
            if (i == 0 || isspace(dob[i-1])){
                dob[i] = toupper(dob[i]);
            }else{
                dob[i] = tolower(dob[i]);
            }
        }
        cout << "  Date of Birth: " << dob << endl;
        cout << "  CNIC Number:   " << cnic << endl;
        cout << "------------------------------------------------------" << endl;
        cout << " Question # | User Choice | Correct Answer |  Result" << endl;
        cout << "------------------------------------------------------" << endl;
        for (int i = 0; i < questions.size(); i++) {
            char correctAnswerIndex = ' ';
            for (int j = 0; j < questions[i].getOptions().size(); j++) {
                if (questions[i].getOptions()[j] == questions[i].getAnswer()) {
                    correctAnswerIndex = (char)('A' + j);
                    break;
                }
            }
            if (questions[i].isSkipped()) {
                 cout << "     "<<(i + 1) << "\t    |      -\t  |       " << correctAnswerIndex << "\t   | Skipped" << endl;
            } else {
                cout << "     "<<(i + 1) << "\t    |      " << questions[i].getUserChoice() << "\t  |       " << correctAnswerIndex << "\t   | " << (questions[i].getUserChoice() == correctAnswerIndex ? "Correct" : "Incorrect") << endl;
            }
        }
        cout << "------------------------------------------------------" << endl;
        cout << "\n" << endl;
        cout<< Spaces<<"\t       _________________________"<<endl;
        cout<< Spaces<<"\t      |  _____________________  |"<<endl;
        cout<< Spaces<<"\t      | |                     | |"<<endl;
        cout<< Spaces<<"\t      | |  Skipped Questions  | |"<<endl;
        cout<< Spaces<<"\t      | |_____________________| |"<<endl;
        cout<< Spaces<<"\t      |_________________________|\n\n"<<endl;
        cout << "------------------------------------------------------" << endl;
        cout << " Question # | User Choice | Correct Answer | Result" << endl;
        cout << "------------------------------------------------------" << endl;
        for (int i = 0; i < skippedQuestions.size(); i++){
            int questionIndex = skippedQuestions[i];
            char correctAnswerIndex = ' ';
            for (int j = 0; j < questions[questionIndex].getOptions().size(); j++){
                if (questions[questionIndex].getOptions()[j] == questions[questionIndex].getAnswer()){
                    correctAnswerIndex = (char)('A'+j);
                    break;
                }
            }
            if (questions[questionIndex].getAttempts() > 1){
                cout << " " <<(questionIndex + 1)<< "\t | -\t "<<correctAnswerIndex<< "\t | Skipped"<<endl;
            }else{
                cout << " "<<(questionIndex + 1)<< "\t | "<<questions[questionIndex].getUserChoice()<< "\t | "<< correctAnswerIndex<< "\t | "<< (questions[questionIndex].getUserChoice() == correctAnswerIndex ? "Correct" : "Incorrect")<<endl;
            }
        }
            cout << "------------------------------------------------------\n\n" << endl;
            cout<< Spaces<<"\t       _______________________"<<endl;
            cout<< Spaces<<"\t      |  ___________________  |"<<endl;
            cout<< Spaces<<"\t      | |                   | |"<<endl;
            cout<< Spaces<<"\t      | |    S T A T U S    | |"<<endl;
            cout<< Spaces<<"\t      | |___________________| |"<<endl;
            cout<< Spaces<<"\t      |_______________________|\n\n"<<endl;
        /*for (int i = 0; i < skippedQuestions.size(); i++) {
            int questionIndex = skippedQuestions[i];
            char correctAnswerIndex = ' ';
            for (int j = 0; j < questions[questionIndex].getOptions().size(); j++) {
                if (questions[questionIndex].getOptions()[j] == questions[questionIndex].getAnswer()) {
                    correctAnswerIndex = (char)('A' + j);
                    break;
                }
            }
            //if (questions[i].isSkipped()) {
                 //cout << "      "<<(i + 1) << "\t    |      -\t  |       " << correctAnswerIndex << "\t   | Skipped" << endl;
            //}else{
                cout << "      "<<(questionIndex + 1) << "\t    |      " << questions[questionIndex].getUserChoice() << "\t  |       " << correctAnswerIndex << "\t   | " << (questions[questionIndex].getUserChoice() == correctAnswerIndex ? "Correct" : "Incorrect") << endl;
            //}

            }
            cout << "------------------------------------------------------" << endl;
            //cout << "\n  You scored " << correctCount << " out of " << questions.size() << endl;
            double percentage = (double)correctCount / questions.size() * 100;
            //cout << "  Percentage: " << percentage << "%" << endl;
            //cout<< "  Position: ";
            */
           double percentage = (double)correctCount / questions.size() * 100;
           string position;
           if (percentage >= 90){
                position = "1st";
            }else if(percentage >= 80){
                position = "2nd";
            }else if(percentage >= 70){
                position = "3rd";
            }else if(percentage >= 60){
                position = "4th";
            }else if(percentage >= 50){
                position = "5th";
            }else if(percentage >= 40){
                position = "6th";
            }else if(percentage >= 30){
                position = "7th";
            }else if(percentage >= 20){
                position = "8th";
            }else if(percentage >= 10){
                position = "9th";
            }else{
                position = "10th";
            }
           if (percentage >= 80 && percentage <= 100){
                cout << "  Hello, Mr. / Miss "<<name<<" son / daughter of "<<fatherName<<", you have scored "<<correctCount<<" out of "<<questions.size()<<endl;
                cout<< "  and secured an impressive "<<percentage<<"% percentage and achieved an outstanding "<<position<<" postion! Excellent work! You're a true champion."<<endl;
           }else if (percentage >= 60 && percentage <= 79){
                cout << "  Hello, Mr. / Miss "<<name<<" son / daughter of "<<fatherName<<", you have scored "<<correctCount<<" out of "<<questions.size()<<endl;
                cout<< "  and secured "<<percentage<<"% percentage and achieved "<<position<<" postion! Great effort! You're on the right track, keep pushing forward!"<<endl;
           }else if (percentage >= 40 && percentage <= 59){
                cout << "  Hello, Mr. / Miss "<<name<<" son / daughter of "<<fatherName<<", you have scored "<<correctCount<<" out of "<<questions.size()<<endl;
                cout<< "  and secured "<<percentage<<"% percentage and achieved "<<position<<" postion! Good job! You're getting closer, stay focused and keep improving!"<<endl;
           }else if (percentage >= 20 && percentage <= 39){
                cout << "  Hello, Mr. / Miss "<<name<<" son / daughter of "<<fatherName<<", you have scored "<<correctCount<<" out of "<<questions.size()<<endl;
                cout<< "  and secured "<<percentage<<"% percentage and achieved "<<position<<" postion! Fair efforts! Keep working hard and you'll see improvement soon!"<<endl;
           }else if (percentage >= 0 && percentage <= 19){
                cout << "  Hello, Mr. / Miss "<<name<<" son / daughter of "<<fatherName<<", you have scored "<<correctCount<<" out of "<<questions.size()<<endl;
                cout<< "  and secured "<<percentage<<"% percentage and achieved "<<position<<" postion! Don't be disheartened! You've started, and that's something; keep going, you'll get better!"<<endl;
           }
        }
};
int main() {
        Quiz quiz("When did Pakistan gain independence?", "1947", {"1947", "1956", "1965", "1971"});
        quiz.addQuestion(QuizQuestion("Who led the Pakistan Movement for independence from British rule?", "Muhammad Ali Jinnah", {"Allama Iqbal", "Liaquat Ali Khan", "Muhammad Ali Jinnah", "Muhammad Ali Bogra"}));
        quiz.addQuestion(QuizQuestion("What was the name of the first President of Pakistan?", "Iskander Mirza", {"Ayub Khan", "Yahya Khan", "Ghulam Ishaq Khan", "Iskander Mirza"}));
        quiz.addQuestion(QuizQuestion("Which agreement was signed between India and Pakistan in 1960 regarding the sharing of the waters of the Indus River and its tributaries?", "Indus Waters Treaty", {"Lahore Declaration", "Tashkent Agreement", "Indus Waters Treaty", "Shimla Agreement"}));
        quiz.addQuestion(QuizQuestion("What was the name of the military operation undertaken by Pakistan in 1999 in the Kargil district of Kashmir?", "Kargil War", {"Operation Swift Retort", "Kargil War", "Operation Gibraltar", "Operation Rah-e-Rast"}));
        quiz.addQuestion(QuizQuestion("Who was the first Chief Martial Law Administrator of Pakistan?", "Ayub Khan", {"Iskander Mirza", "Ayub Khan", "Yahya Khan", "Zia-ul-Haq"}));
        quiz.addQuestion(QuizQuestion("Which event led to the separation of East Pakistan, now known as Bangladesh, from West Pakistan?", "Indo-Pakistani War of 1971", {"Partition of India", "Simla Agreement", "Indo-Pakistani War of 1971", "Tashkent Agreement"}));
        quiz.addQuestion(QuizQuestion("Who founded the city of Lahore?", "Mughal Emperor Akbar", {"Sikh Emperor Ranjit Singh", "Mughal Emperor Akbar", "British Governor-General John Lawrence", "Arab General Muhammad bin Qasim"}));
        quiz.addQuestion(QuizQuestion("Which ancient civilization flourished in the Indus Valley region of Pakistan?", "Mohenjo-Daro", {"Taxila", "Gandhara", "Harappa", "Mohenjo-Daro"}));
        quiz.addQuestion(QuizQuestion("Which province of Pakistan is rich in coal deposits?", "Balochistan", {"Khyber Pakhtunkhwa", "Punjab", "Balochistan", "Sindh"}));
        quiz.addQuestion(QuizQuestion("Which river is a major source of hydroelectric power in Pakistan?", "Indus River", {"Indus River", "Chenab River", "Ravi River", "Sutlej River"}));
        quiz.addQuestion(QuizQuestion("Which mountain range is located in the northwest of Pakistan and extends into Afghanistan?", "Hindu Kush", {"Himalayas", "Hindu Kush", "Pamir Mountains", "Karakoram Range"}));
        quiz.addQuestion(QuizQuestion("Which mountain range runs along the northern border of Pakistan?", "Karakoram", {"Karakoram", "Himalayas", "Hindu Kush", "Tian Shan"}));
        // More Question...
        string Spaces = "\t\t\t\t";
        cout<< Spaces<<" ________________________________________________"<<endl;
        cout<< Spaces<<"|  ____________________________________________  | "<<endl;
        cout<< Spaces<<"| |                                            | |"<<endl;
        cout<< Spaces<<"| |            W E L C O M E     T O           | |"<<endl;
        cout<< Spaces<<"| |                                            | |"<<endl;
        cout<< Spaces<<"| |     Q U I  Z     A P P L I C A T I O N     | |"<<endl;
        cout<< Spaces<<"| |____________________________________________| |"<<endl;
        cout<< Spaces<<"|________________________________________________| \n"<<endl;
        string Play;
        cout << "  Do you want to play quiz game?\n  1. Yes\n  2. No\n  Your choice is: ";
        getline(cin,Play);
        if (Play == "1" || Play == "yes" || Play == "Yes"){
            quiz.displayQuestions();
        }else if (Play == "2" || Play == "no" || Play == "No"){
            string Reason;
            cout << "  Give a solid reason why you do not play quiz game? ";
            getline(cin,Reason);
            system("cls");
            cout <<endl;
            cout<< Spaces<<"\t       _______________________"<<endl;
            cout<< Spaces<<"\t      |  ___________________  |"<<endl;
            cout<< Spaces<<"\t      | |                   | |"<<endl;
            cout<< Spaces<<"\t      | |    R E S U L T    | |"<<endl;
            cout<< Spaces<<"\t      | |___________________| |"<<endl;
            cout<< Spaces<<"\t      |_______________________|\n\n"<<endl;
            cout<<"  Hello, we missed you in the quiz game! Unfortunately, you didn't participate.\n  Reason: "<<Reason;
            cout<<". \n \tThat's okay, we completely understand. Life can get overwhelming, and priorities shift. No worries, come back \n \twhen you're ready and comfortable!"<<endl;
            cout<<"\tTake care of yourself too much!"<<endl;
        }else{
            cout << "\n  I N V A L I D   O P T I O N   T R Y   A G A I N" <<endl;
        }


    return 0;
}
