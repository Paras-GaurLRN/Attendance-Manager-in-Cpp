#include <iostream> // For debugging, remove later
#include <vector>

/*Custom Exceptions*/
class invalid_input : public std::exception
{
    public:
    virtual const char* what() const noexcept {
        return "Please Enter Valid Input!\n";
    }
};

class marks_not_assigned : public std::exception
{
    public:
    virtual const char* what() const noexcept {
        return "Please Assign Marks Before Acessing It!\n";
    }
};

/*Attendance Handeling*/

class ATTENDANCE_t {
    private:
    bool state;

    public:
    ATTENDANCE_t() = delete;

    explicit ATTENDANCE_t(char ch) noexcept(false) {
        if(ch == 'p' || ch == 'P' || ch == 't' || ch == 'T') {state = true;}
        else if(ch == 'a' || ch == 'A' || ch == 'f' || ch == 'F') {state = false;}
        else{throw invalid_input();}
    }

    explicit ATTENDANCE_t(bool flag) noexcept {state = flag;}

    ATTENDANCE_t operator!() const noexcept {return ATTENDANCE_t(!state);}

    friend std::ostream& operator<<(std::ostream& os, const ATTENDANCE_t at)
    {std::string output = (at.state) ? ("Present") : ("Absent"); return os << output;}
};

/*Subjects Base Classes*/

class SUBJECT_t {
    protected:
    std::string name;
    short marks;
    const unsigned short max_marks;

    SUBJECT_t() = delete;

    explicit SUBJECT_t(std::string _name, unsigned short _max_marks) noexcept : name(_name), max_marks(_max_marks), marks(-1) {}

    explicit SUBJECT_t(std::string _name, unsigned short _max_marks, int _marks) noexcept(false) : max_marks(_max_marks) {
        if(_marks < 0) {throw invalid_input();}
        else if(_marks > max_marks) {throw invalid_input();}
        name = _name;
        marks = _marks;
    }

    public: // How to make it so that only called from derived classes?
    unsigned short getMarks() const noexcept(false) {
        if(marks < 0) {throw marks_not_assigned();}
        return marks;
    }

    void setMarks(int _marks) noexcept(false) {
        if(_marks < 0) {throw invalid_input();}
        else if(_marks > max_marks) {throw invalid_input();}
        else if(marks == -1){marks = _marks;}
        else
        {
// How to make it so that this asks for password before updating marks?
        }
    }
};

class SUBJECT_template : public SUBJECT_t {
    public:
    SUBJECT_template() = delete;
    
    explicit SUBJECT_template(std::string _name, unsigned short _max_marks) noexcept : SUBJECT_t(_name, _max_marks) {}

    explicit SUBJECT_template(std::string _name, unsigned short _max_marks, int _marks) noexcept(false)
    : SUBJECT_t(_name, _max_marks, _marks) {}
};

/*
template <class T>
class SUBJECT_CONTAINER_t {
    static_assert(std::is_base_of<SUBJECT_t, T>::value, "T must be derived from SUBJECT_t");
    // For Compile Time Checking

    private:
    std::vector<SUBJECT_t*> subjects;

    public:
    SUBJECT_CONTAINER_t() = delete;

    SUBJECT_CONTAINER_t(std::vector<SUBJECT_t*> _subjects) noexcept : subjects(_subjects) {}

    friend void operator +(SUBJECT_CONTAINER_t& sc, SUBJECT_t* sub) noexcept {
        sc.subjects.push_back(sub);
    }
};

Yet To Be Finished
*/

/*Date Datatype Class and handeling*/
class DATE_t{};

/*Each Student Data Class Stuff*/
class STUDENT_t {

};

class STUDENT_RECORD_t{};

/*Making The Full Data Storage Structure (3-D Table)*/

class DATA_CUBE{}; // This will ensure that data is consistent and properly connected

/*Debugging Use Only*/

main()
{
    try{
        char c; std::cout << "Enter Input : "; std::cin >> c;
        ATTENDANCE_t AT1(c);
        std::cout << AT1;
    }
    catch (invalid_input& e)
    {
        std::cout << e.what();
    }
}