#include <iostream> // For debugging, remove later
#include <vector>


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

class STUDENT_t {

};

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

class SUBJECT_t {
    protected:
    std::string name;
    short marks;
    const unsigned short max_marks;

    SUBJECT_t() = delete;

    SUBJECT_t(std::string _name, unsigned short _max_marks) noexcept : name(_name), max_marks(_max_marks), marks(-1) {}

    explicit SUBJECT_t(std::string _name, unsigned short _max_marks, int _marks) noexcept(false) : max_marks(_max_marks) {
        if(_marks < 0) {throw invalid_input();}
        name = _name;
        marks = _marks;
    }

    public:
    unsigned short getMarks() const noexcept(false) {
        if(marks < 0) {throw marks_not_assigned();}
        return marks;
    }
};

class DATE_t{};

class STUDENT_RECORD_t{};

class DATA_CUBE{}; // This will ensure that data is consistent and properly connected

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