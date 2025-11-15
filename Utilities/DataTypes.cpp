#include <iostream> // For debugging, remove later
#include <vector>


class invalid_input : public std::exception
{
    public:
    virtual const char* what() const noexcept {
        return "Please Enter Valid Input!\n";
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

class SUBJECT_t{};

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