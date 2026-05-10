#include <iostream> // For debugging, remove later
#include <vector>
#include <ctime>

// /*Password Check*/ needs to be replaced with actual password handling mechanism

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

class SSD_TABLE_already_exists : public std::exception
{
    public:
    virtual const char* what() const noexcept {
        return "SSD_TABLE Instance Already Exists!\n";
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

class SUBJECT_base {
    protected:
    std::string id;
    unsigned short marks;
    const unsigned short max_marks;

    SUBJECT_base() = delete;

    explicit SUBJECT_base(std::string _id, unsigned short _max_marks) noexcept 
    : id(_id), max_marks(_max_marks), marks(-1) {}

    explicit SUBJECT_base(std::string _id, unsigned short _max_marks, int _marks) noexcept(false)
    : id(_id), max_marks(_max_marks) {}
};

class SUBJECT_t : public SUBJECT_base {
    private:
    unsigned short validateMarks(int _marks) noexcept(false) {
        if(_marks < 0) {throw invalid_input();}
        else if(_marks > max_marks) {throw invalid_input();}
        return static_cast<unsigned short>(_marks);
    }

    public:
    SUBJECT_t() = delete;
    
    explicit SUBJECT_t(std::string _id, unsigned short _max_marks) noexcept : SUBJECT_base(_id, _max_marks) {}

    explicit SUBJECT_t(std::string _id, unsigned short _max_marks, int _marks) noexcept(false)
    : SUBJECT_base(_id, _max_marks, validateMarks(_marks)) {}

    unsigned short getMarks() const noexcept(false) {
        if(marks == -1) {throw marks_not_assigned();}
        return marks;
    }

    void setMarks(int _marks) noexcept(false) {
        if(_marks < 0) {throw invalid_input();}
        else if(_marks > max_marks) {throw invalid_input();}
        else if(marks == -1){marks = _marks;}
        else {/*Password Check*/marks = _marks;}
    }
};

/* Most probably going to be depricated beacuse of data storage structure change

template <class SUB>
class SUBJECT_CONTAINER_t {
    static_assert(std::is_base_of<SUBJECT_t, SUB>::value, "T must be derived from SUBJECT_base");
    // For Compile Time Checking

    private:
    std::vector<SUB*> subjects;

    public:
    SUBJECT_CONTAINER_t() = delete;

    SUBJECT_CONTAINER_t(std::vector<SUB*> _subjects) noexcept : subjects(_subjects) {}

    friend void operator +(SUBJECT_CONTAINER_t& sc, SUBJECT_base* sub) noexcept {
        sc.subjects.push_back(sub);
    }
};
*/

/*Date Datatype Class and handeling*/
class DATE_base {
    protected:
    const unsigned short day;
    const unsigned short month;
    const unsigned short year;

    explicit DATE_base(unsigned short _day, unsigned short _month, unsigned short _year) noexcept 
    : day(_day), month(_month), year(_year) {}

};

class DATE_t : public DATE_base{
    private:
    enum{Uninitalized = -1, False, True};
    class trool {
        public:
        short state;

        explicit trool() : state(Uninitalized) {}
        
        operator bool() const noexcept {
            if(state == Uninitalized) {return false;}
            return static_cast<bool>(state);
        }

    } Input_Validity_Flag;

    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    
    public:
    explicit DATE_t() noexcept 
    : DATE_base(static_cast<unsigned short>(now->tm_mday),
                static_cast<unsigned short>(now->tm_mon),
                static_cast<unsigned short>(now->tm_year)) {}

    unsigned short getDay() const noexcept {return day;}
    unsigned short getMonth() const noexcept {return month;}
    unsigned short getYear() const noexcept {return year;}

    // bool isValidDate(unsigned short d, unsigned short m, unsigned short y) const noexcept {
    //     if(m < 1 || m > 12 || d < 1 || y < year) {return false;}

    //     unsigned short days_in_month;
    //     switch(m) {
    //     case 1: case 3: case 5: case 7: case 8: case 10: case 12: {days_in_month = 31; break;}
    //     case 4: case 6: case 9: case 11: {days_in_month = 30; break;}
    //     case 2: {days_in_month = 28;}}
    //     // This is better than a list, as it saves memory, which is more important here
        
    //     if((m == 2) && ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))) {days_in_month++;}
        
    //     if(d > days_in_month) {return false;}
        
    //     return true;
    // }

    // void setDate(unsigned short d, unsigned short m, unsigned short y) noexcept(false) {
    //     // Basic Validation
    //     if(!isValidDate(d, m, y)) {throw invalid_input();}

    //     day = d; month = m; year = y;
    // }

    friend std::ostream& operator<<(std::ostream& os, const DATE_t& dt)
    {
        os << dt.day << "/" << dt.month << "/" << dt.year;
        return os;
    }
};

/*Each Student Data Class Stuff*/
class STUDENT_base {
    protected:
    std::string id;

    STUDENT_base() = delete;
};

class STUDENT_t : STUDENT_base {
    public: enum{Other = -1, Male, Female};
    private:
    std::string name;

    public:
    STUDENT_t() = delete;
    
};

class STUDENT_RECORD_t{};

/*Making The Full Data Storage Structure (3-D Table)*/

class SSD_TABLE {
    // Add Password Protection Later
    private:
    // static_assert(std::is_base_of<SUBJECT_t, SUB>::value, "SUB must be derived from SUBJECT_t");

    std::vector<STUDENT_RECORD_t*> students;
    std::vector<SUBJECT_t*> subjects;
    std::vector<DATE_t*> dates;
    static short count;

    public:
    SSD_TABLE() = delete;

    explicit SSD_TABLE(std::vector<STUDENT_RECORD_t*> _students,
            std::vector<SUBJECT_t*> _subjects,
            std::vector<DATE_t*> _dates) noexcept(false)
    {
        if(count == 1) {throw SSD_TABLE_already_exists();}
        count++;
        students = _students;
        subjects = _subjects;
        dates = _dates;
    }

    ~SSD_TABLE() noexcept {count--;}

    void operator+(STUDENT_RECORD_t* student) noexcept {students.push_back(student);}
    void operator+(SUBJECT_t* subject) noexcept {subjects.push_back(subject);}
    void operator+(DATE_t* date) noexcept {dates.push_back(date);}

}; // This will ensure that data is consistent and properly connected

short SSD_TABLE::count = 0;

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