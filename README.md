# Intelligent-Scissor

This is the first project of HKUST MSc BDT course MSBD 6000C -- Computer Vision.

### Project Description

// to do

### Environment

Programming Language: C++
SDK: Desktop Qt 5.10.0  MSVC 2017 64-bit
OS: Windows 10

### Image Storage Structure

We use user-defined-class imArray to store image pixel information, which is defined as below:

    {
    public:
    
    explicit imArray(QImage *image);
    ~imArray();
    
    private:
    
    QVector<int> vecRed, vecGreen, vecBlue;
    int width, height;
    }

vecRed/vecGreen/vecBlue is a QVector object, with all the elements being integers. To get the pixel with coordinator (x, y), use vecX[y*width + x].
