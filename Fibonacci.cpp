// Fibonacci.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Fibonacci.h" 

struct Vec2
{
    float x;
    float y;
public:
    Vec2(float x, float y) {
        this->x = x;
        this->y = y;
    }
};
static float benchmarkMethod(int n, bigint (*method) (int)) {

    cout << "Fibonacci: " << n << " = ";
    long long startTime = getTimeMS();
    cout << method(n);
    long long duration = getTimeMS() - startTime;
    float time = (float)duration;
    cout << " Duration: ";
    vector<int> digits;
    while (duration)
    {
        digits.push_back(duration % 10);
        duration /= 10;
    }
    for (int i = digits.size() - 1; i >= 0;i--) {

        if ((i + 1) % 3 == 0) {
            cout << " ";
        }
        cout << digits[i];
    }
    cout << "ms" << endl;
    return time;
}

static bool doBenshmark(vector<sf::Vertex> *points,int n, bigint(*method) (int),sf::Color color) {
    /*for (int i = 0;i < points.size();i++)
    {
        points[i].position.x -= 10;
        points[i].position.x /= 1000.0f / (float)points.size();
    }*/
    memo = vector<bigint>({ 0,1 });
    float time = benchmarkMethod(n,method);
    sf::Vertex vert;
    vert.position = vec2(points->size(), 500 - time / 2);
    vert.color = color;
    points->push_back(vert);
    /*for (int i = 0;i < points.size();i++)
    {
        points[i].position.x *= 1000.0f / (float)points.size();
        points[i].position.x += 10;
    }*/
    if (time > 1000) {
        return true;
    }
    return false;
}
vector<sf::Vertex> transformPoints(vector<sf::Vertex> in,int n,int step) {
    vector<sf::Vertex> out;
    for (int i = 0;i < in.size();i++)
    {
        sf::Vertex vert;
        vert.position = vec2(in[i].position.x * (1000.0f / (float)(n / step)) + 10, in[i].position.y);
        vert.color = in[i].color;
        out.push_back(vert);
    }
    return out;
}
struct Algorithm {
public:
    bigint(*code)(int);
    bool exeededTime = false;
    vector<sf::Vertex> points;
    sf::Color color;
    Algorithm(bigint(*code)(int),sf::Color color) {
        this->code = code;
        this->color = color;
    }
};
vector<vector<sf::Vertex>> visualizeMethods(vector<Algorithm> *algorithms,int *n,int step) {
    bool oneNotFinished = false;
    vector<vector<sf::Vertex>> pointsToDraw;
    for (Algorithm &algorithm :*algorithms)
    {
        if (!algorithm.exeededTime) {
            algorithm.exeededTime = doBenshmark(&algorithm.points, *n, algorithm.code, algorithm.color);
            oneNotFinished = true;
        }
        pointsToDraw.push_back(transformPoints(algorithm.points, *n, step));
    }
    if (oneNotFinished) {
        *n += step;
    }
    return pointsToDraw;
}

int main()
{
    int n = 0,step = 50;
    
    sf::RenderWindow window(sf::VideoMode({ 1020, 510 }), "SFML works!");
    sf::Vertex axes[4];
    vector<Algorithm> algorithms;
    vector<vector<sf::Vertex>> pointsToDraw;
    //algorithms.push_back(Algorithm(&fibBottomUp, sf::Color(255, 0, 0)));
    algorithms.push_back(Algorithm(&fibMatrix, sf::Color(0,255, 0)));
    algorithms.push_back(Algorithm(&fibMatrixBinExp, sf::Color(0,0,255)));
    algorithms.push_back(Algorithm(&fibMatrixFastExp, sf::Color(255, 0, 0)));
    setupAxes(&axes[0]);
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.draw(&axes[0], 4, sf::PrimitiveType::Lines);
        pointsToDraw = visualizeMethods(&algorithms, &n, step);

        for (vector<sf::Vertex>& points : pointsToDraw)
        {
            window.draw(&points[0], points.size(), sf::PrimitiveType::LineStrip);
        }
        window.display();
    }
    return 0;
}


