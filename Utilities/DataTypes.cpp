#include <iostream> // For debugging, remove later
#include <vector>
#include <ctime>

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
    std::string id;
    short marks;
    const unsigned short max_marks;

    SUBJECT_t() = delete;

    explicit SUBJECT_t(std::string _id, unsigned short _max_marks) noexcept : id(_id), max_marks(_max_marks), marks(-1) {}

    explicit SUBJECT_t(std::string _id, unsigned short _max_marks, int _marks) noexcept(false) : max_marks(_max_marks) {
        if(_marks < 0) {throw invalid_input();}
        else if(_marks > max_marks) {throw invalid_input();}
        id = _id;
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
    
    explicit SUBJECT_template(std::string _id, unsigned short _max_marks) noexcept : SUBJECT_t(_id, _max_marks) {}

    explicit SUBJECT_template(std::string _id, unsigned short _max_marks, int _marks) noexcept(false)
    : SUBJECT_t(_id, _max_marks, _marks) {}
};

/* Most probably going to be depricated beacuse of data storage structure change

template <class SUB>
class SUBJECT_CONTAINER_t {
    static_assert(std::is_base_of<SUBJECT_template, SUB>::value, "T must be derived from SUBJECT_t");
    // For Compile Time Checking

    private:
    std::vector<SUB*> subjects;

    public:
    SUBJECT_CONTAINER_t() = delete;

    SUBJECT_CONTAINER_t(std::vector<SUB*> _subjects) noexcept : subjects(_subjects) {}

    friend void operator +(SUBJECT_CONTAINER_t& sc, SUBJECT_t* sub) noexcept {
        sc.subjects.push_back(sub);
    }
};
*/

/*Date Datatype Class and handeling*/
class DATE_t {
    private:
    unsigned short day;
    unsigned short month;
    unsigned short year;

    public:
    explicit DATE_t() noexcept {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        day = now->tm_mday;
        month = now->tm_mon + 1;
        year = now->tm_year + 1900;
    }

    bool isValidDate(unsigned short d, unsigned short m, unsigned short y) const noexcept {
        if(m < 1 || m > 12 || d < 1 || y < year) {return false;}

        unsigned short days_in_month;
        switch(m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: {days_in_month = 31; break;}
        case 4: case 6: case 9: case 11: {days_in_month = 30; break;}
        case 2: {days_in_month = 28;}}
        // This is better than a list, as it saves memory, which is more important here
        
        if((m == 2) && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) {days_in_month++;}
        
        if(d > days_in_month) {return false;}
        
        return true;
    }

    void setDate(unsigned short d, unsigned short m, unsigned short y) noexcept(false) {
        // Basic Validation
        if(!isValidDate(d, m, y)) {throw invalid_input();}

        day = d; month = m; year = y;
    }

    friend std::ostream& operator<<(std::ostream& os, const DATE_t& dt)
    {
        os << dt.day << "/" << dt.month << "/" << dt.year;
        return os;
    }
};

/*Each Student Data Class Stuff*/
class STUDENT_t {

};

class STUDENT_RECORD_t{};

/*Making The Full Data Storage Structure (3-D Table)*/

template <class SUB_t>
class SSD_TABLE {
    // Add Password Protection Later
    private:
    static_assert(std::is_base_of<SUBJECT_template, SUB>::value, "SUB must be derived from SUBJECT_template");

    std::vector<STUDENT_RECORD_t*> students;
    std::vector<SUB_t*> subjects;
    std::vector<DATE_t*> dates;
    static short count;

    public:
    SSD_TABLE() = delete;

    explicit SSD_TABLE(std::vector<STUDENT_RECORD_t*> _students,
            std::vector<SUB_t*> _subjects,
            std::vector<DATE_t*> _dates) noexcept(false)
    {
        if(count == 1) {throw std::runtime_error("SSD_TABLE Instance Already Exists!");}
        count++;
        students = _students;
        subjects = _subjects;
        dates = _dates;
    }

    void operator+(STUDENT_RECORD_t* student) noexcept {students.push_back(student);}
    void operator+(SUB_t* subject) noexcept {subjects.push_back(subject);}
    void operator+(DATE_t* date) noexcept {dates.push_back(date);}

}; // This will ensure that data is consistent and properly connected

template <class SUB_t>
short SSD_TABLE<SUB_t>::count = 0;

/*Debugging Use Only*/

int main()
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