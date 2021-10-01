# Table of Contents:
### [1. Hướng dẫn sử dụng chi tiết các file trong các folder](#1)

- #### [Header](#11)
- #### [Creator](#12)
- #### [Resources](#13)

  - ##### [NoteForAProblem.txt](#131)
  - ##### [Description.docx](#132)
  - ##### [PrimeNumbers.txt](#133)

- #### [Solutions](#14)
- #### [TimeChecker](#15)
- #### [Packager.py](#16)
- #### [Generator.cpp](#17)

### [2. Hướng dẫn tạo một Problem](#2)

### [3. ITPlib.hpp's Funtions](#3)

# Contents:  

<a name = "1"></a>
### 1. Hướng dẫn sử dụng chi tiết các file trong các folder

<a name = "11"></a>
### Header
<a name = "111"></a>
- **ITPlib.hpp**: 
       Thư viện tự viết.
<a name = "112"></a>
- **Setup.hpp**: 
       Nơi chỉnh sửa chính về cả nội dung và số lượng của các file test case. Mặc định có 3 độ khó Easy, Medium, Hard, nếu cần thêm level có thể gỡ cmt và dùng thêm hàm NightMare đã có sẵn.
<a name = "12"></a>
### Creator
- **InCreator (Không sửa)**:
       Script sinh file in của test cases. Sử dụng các hàm được edit trong Setup.hpp.
- **OutCreator (Không sửa)**:
       Script sinh file in của test cases.
<a name = "13"></a>
### Resources

Vai trò như tên, chứa tài nguyên hỗ trợ. Có 2 file cần chú ý đó là:
<a name = "131"></a>
- **NoteForAProblem.txt**: 
       File này dùng để note lại các vấn đề mà người ra đề cần truyền đạt lại với người up đề. Yêu cầu **chỉ chỉnh sửa nội dung và không làm gì khác ngoài chỉnh sửa nội dung.**
<a name = "132"></a>
- **Description.docx**: 
       File đã để sẵn form đề thi, yêu cầu **đưa đề thi đúng format vào đây và không làm gì khác**.
<a name = "133"></a>
- **PrimeNumbers.txt**:
       Tất cả các số nguyên tố nhỏ hơn 1e8, sắp xếp lần lượt theo dòng.
<a name = "14"></a>
### Solutions 
Folder chứa solutions - các cách giải, các file được tùy chỉnh nhưng **code được sử dụng để sinh test sẽ giữ ở file `MainSolution.cpp`**.
<a name = "15"></a>

### TimeChecker
Folder chứa C++ script để đo và so sánh thời gian chạy của các phương pháp (method) cần test. Mỗi method là một file code c/c++ của người dùng. Sử dụng script này bằng cách **đưa methods vào folder này** và Compile&Run `Comparator.cpp`.


Trong script có một biến bool cleanMode quản lý chế độ cleanMode. Nếu không sử dụng cleanMode, sau khi chạy Comparator.exe, trong folder sẽ có một folder Temp chứa các folder con, mỗi folder con này lại chứa test sinh out của từng method, có thể dựa vào đây để xem các method có chạy đúng hoàn toàn hay không. Nếu dùng cleanMode, folder Temp và các file exe compile từ methods sẽ bị xóa.

<a name = "16"></a>
### Packager.py
Là python script để đóng gói, nó sẽ tự động sinh ra và zip 1 folder chứa:

- Problem.docx (lấy nội dung từ Description.docx).
- Note.txt (lấy nội dung từ NoteForAProblem.txt).
- Setup.hpp.
- Solutions's folder.
- Test cases's folder.

#### File zip này là file zip của đề với fomart tên `Problem<input>.zip` - input là tên Problem người dùng nhập vào, nếu cần package và gửi đi thì chỉ cần file này là đủ.`

<a name = "17"></a>

### Generator.cpp

Để đảm bảo file zip package được là bản final, trước khi sử dụng script này, cần phải đảm bảo nội dung folders và các file sau là đã hoàn thành:

- Solutions
- Setup.hpp
- NoteForAProblem.txt
- Description.docx

Script này tự động hóa quá trình: `Sinh test in -> Sinh test out -> Dọn file exe -> Package project(nếu đã cài python)`. 

<a name = "2"></a>
## 2. Hướng dẫn tạo một Problem

#### Bước 0: Thực hiện:
- Sửa nội dung Description.docx thành nội dung đề. 
- Sửa nội dung NoteForAProblem.txt thành nội dung cần note. 
- Đảm bảo code solution đúng. 
- **Không đổi tên bất kỳ file nào có sẵn.**

#### Bước 1: Mở và sửa các nội dung trong Setup.hpp:
- Các biến:
  - inf.number_of_test_case: quyết định số lượng test case sinh ra.
  - inf.limit_size_of_file: đưa ra giới hạn dung lượng các file được sinh.
- Các hàm: 

Sửa các hàm Easy, Medium, Hard (và cả NightMare nếu cần). Các hàm này sẽ là hàm sinh nội dung cho những file input của test case.
       
#### Bước 2: Lưu file Setup.hpp. 

- Hướng 1 (thủ công): Chạy Creator's script(In rồi Out), package bẳng cách chạy Packager.py.
- Hướng 2 (tự động): Sử dụng Generator. Nếu cần package mà chưa cài python, tự zip 1 folder bằng tay theo mẫu ở trên.

#### Bước 3: Xong.

<a name = "3"></a>
## 3. ITPlib.hpp's Funtions

*Đa phần funtions đều được viết theo dạng template nên không cần quá lo về kiểu dữ liệu.*

- **Class BigInt cho số nguyên lớn gần như đầy đủ operator**.

- **Một số hàm kiểm tra tiến độ khi sinh test case**.

- **Random & Shuffle**:
  - Random số nguyên từ left -> right với randll(left, right).
  - Random số thực từ left -> right với randdb(left, right).
  - Random BigInt có numOfDigits chữ số với randBigInt(numOfDigits).
  - Random BigInt từ left -> right với randBigInt(left, right), không recommend dùng hàm này vì tính ngẫu nhiên còn thấp.
  - vector <Type> randUniqueArr(N, left, right): Random một vector có N phần tử với giá trị trong [left, right]. Nó không chứa phần tử trùng nhau và xếp theo thứ tự ngẫu nhiên.
  - void ArrShuff(arr): Tráo ngẫu nhiên các phần tử trong mảng arr.

- **Số nguyên tố**:
  - int primeTh(n): Số nguyên tố thứ n. (1 < n < 5761455)
  - bool isPrime(N): Kiểm tra N có là số nguyên tố không trong O(sqrt(n)/6).
  - vector <int> primeListBySerial(left, right) : List số nguyên tố từ left -> right theo serial (số thứ tự).
  - vector <int> primeListByValue(left, right): List số nguyên tố từ left -> right theo đoạn [L, R] (R < 1e8).
  - vector <long long> EratosthenesOnRange(L, R): Sàng Eratosthenes trong đoạn [L, R] với L, R có thể là số lớn. Trả về vector chứa các số nguyên tố trong [L, R]

- **Palindrome (cấu trúc đối xứng)**:
  - bool isPalindrome(var): Kiểm tra var có phải một biến đối xứng hay không.
  - bool isPalindromeArray(arr): Kiểm tra một array có đối xứng hay không.
  - bool isPalindromeSContainer(SC): Kiểm tra một STL Sequence Container có đối xứng hay không.

- **Khác**:
  - bool isInteger(num): Kiểm tra num có là số nguyên không.
  - bool isSquareNum(num): Kiểm tra num có là số chính phương không.
  - map <int, int> factorAnalyze(num): Phân tích thừa số nguyên tố của num với map chứa các phần tử `(ước nguyên tố; mũ)`.
  - vector <ll> divisorsOf(num): Tìm list ước của num.
  - int numOfDivisors(num): Tìm số lượng ước của số num.
