#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

void in(float** a, float c, float n)
{
    std::ifstream in("Input.csv");
    for (int i = 0; i < n; i++)
    {
        in >> a[i][0] >> a[i][1];
    }
}

float roundx(float m, int n)
{
    int exp = static_cast<int>(std::floor(std::log10(std::abs(m))));
    double val = std::pow(10, n - exp);
    float tmp = round(m * val) / val;
    return tmp;
}

void colSi(float** a, double c, float n, float Si[])
{
    for (int i = 0; i < n; i++)
    {
        Si[i] = 0.354 * a[i][0] / a[i][1];
    }
}

float avrgS(float c, float n, float Si[])
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum = sum + roundx(Si[i], 1);
    }
    return sum / n;
}

float Km(float c, float n, float Si[])
{
    float Sm = roundx(avrgS(c, n, Si), 1);
    return Sm / 0.6; // 0.6 - среднее значение Sy
}

void out(float** a, float c, float n, float Si[])
{
    colSi(a, c, n, Si);
    std::ofstream out("Output.csv");
    for (int i = 0; i < n; i++)
    {
        out << std::setprecision(2) << Si[i] << std::endl;
    }

    out << std::endl << std::setprecision(2) << avrgS(c, n, Si) << std::endl;
    out << std::setprecision(2) << Km(c, n, Si) << std::endl;
}

int main()
{
    float c = 2;
    float n = 5;
    float** a = new float* [n];
    for (int i = 0; i < n; ++i)
    {
        a[i] = new float[c];
    }

    float Si[5];
    in(a, c, n);
    out(a, c, n, Si);

    return EXIT_SUCCESS;
}