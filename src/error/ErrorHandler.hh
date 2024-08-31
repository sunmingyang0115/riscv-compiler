// #ifndef ERROR_HANDLER_H
// #define ERROR_HANDLER_H
// #include <string>

// namespace ErrorHandle {
// /**
//  * A class that represents an 'Error' type
//  */
// class Error {
// private:
//     int position[2];
//     int length;
//     std::string errorDescription;

// public:
//     Error(int position[2], int length, std::string errorDescription);
//     ~Error();
//     std::string generateErrorMessage();
// };

// template <typename T>
// struct Result {
//     bool isSucessful;
//     union {
//         T *expr;
//         ErrorHandler *error;
//     };
// };

// } // namespace Error

// #endif