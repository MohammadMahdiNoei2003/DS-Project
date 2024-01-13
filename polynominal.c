#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 100
#define EPSILON 0.0001
#define MAX_ITERATIONS 100

// Function to read coefficients of a polynomial from the user
void readPolynomial(int polynomial[], int degree) {
    printf("Enter the coefficients of the polynomial: ");
    for (int i = 0; i <= degree; i++) {
        scanf("%d", &polynomial[i]);
    }
}

// Function to print a polynomial
void printPolynomial(const int polynomial[], int degree) {
    printf("Polynomial: ");
    for (int i = degree; i >= 0; i--) {
        printf("%dx^%d ", polynomial[i], i);
        if (i > 0) {
            printf("+ ");
        }
    }
    printf("\n");
}

// Function to add two polynomials
void addPolynomials(const int poly1[], const int poly2[], int result[], int degree) {
    for (int i = 0; i <= degree; i++) {
        result[i] = poly1[i] + poly2[i];
    }
}

// Function to subtract two polynomials
void subtractPolynomials(const int poly1[], const int poly2[], int result[], int degree) {
    for (int i = 0; i <= degree; i++) {
        result[i] = poly1[i] - poly2[i];
    }
}

// Function to multiply two polynomials
void multiplyPolynomials(const int poly1[], const int poly2[], int result[], int degree1, int degree2) {
    for (int i = 0; i <= degree1 + degree2; i++) {
        result[i] = 0;
    }

    for (int i = 0; i <= degree1; i++) {
        for (int j = 0; j <= degree2; j++) {
            result[i + j] += poly1[i] * poly2[j];
        }
    }
}

// Function to evaluate a polynomial at a given value of x
double evaluatePolynomial(const int polynomial[], int degree, double x) {
    double result = 0.0;

    for (int i = degree; i >= 0; i--) {
        result += polynomial[i] * pow(x, i);
    }

    return result;
}

// Function to evaluate the derivative of a polynomial at a given value of x
double evaluatePolynomialDerivative(const int polynomial[], int degree, double x) {
    double result = 0.0;

    for (int i = degree; i > 0; i--) {
        result += i * polynomial[i] * pow(x, i - 1);
    }

    return result;
}

// Function to find the root of a polynomial using the Newton method
double findRoot(const int polynomial[], int degree, double initialGuess) {
    double x = initialGuess;
    int iterations = 0;

    while (fabs(evaluatePolynomial(polynomial, degree, x)) > EPSILON && iterations < MAX_ITERATIONS) {
        double fx = evaluatePolynomial(polynomial, degree, x);
        double fxDerivative = evaluatePolynomialDerivative(polynomial, degree, x);

        if (fabs(fxDerivative) < EPSILON) {
            break;  // Avoid division by zero
        }

        x = x - (fx / fxDerivative);
        iterations++;
    }

    return x;
}

int main() {
    int degree1, degree2;
    int polynomial1[MAX_DEGREE + 1], polynomial2[MAX_DEGREE + 1];
    int sum[MAX_DEGREE + 1], difference[MAX_DEGREE + 1], product[MAX_DEGREE * 2 + 1];

    printf("Enter the degree of the first polynomial: ");
    scanf("%d", &degree1);
    readPolynomial(polynomial1, degree1);

    printf("Enter the degree of the second polynomial: ");
    scanf("%d", &degree2);
    readPolynomial(polynomial2, degree2);

    addPolynomials(polynomial1, polynomial2, sum, degree1 > degree2 ? degree1 : degree2);
    subtractPolynomials(polynomial1, polynomial2, difference, degree1 > degree2 ? degree1 : degree2);
    multiplyPolynomials(polynomial1, polynomial2, product, degree1, degree2);

    printf("\n");
    printPolynomial(polynomial1, degree1);
    printPolynomial(polynomial2, degree2);

    printf("\nSum: ");
    printPolynomial(sum, degree1 > degree2 ? degree1 : degree2);

    printf("Difference: ");
    printPolynomial(difference, degree1 > degree2 ? degree1 : degree2);

    printf("Product: ");
    printPolynomial(product, degree1 + degree2);

    printf("\nFinding roots of the first polynomial:\n");
    for (int i = 0; i <= degree1; i++) {
        double root = findRoot(polynomial1, degree1, i);
        printf("Root %d: %lf\n", i + 1, root);
    }

    printf("\nFinding roots of the second polynomial:\n");
    for (int i = 0; i <= degree2; i++) {
        double root = findRoot(polynomial2, degree2, i);
        printf("Root %d: %lf\n", i + 1, root);
    }

    return 0;
}