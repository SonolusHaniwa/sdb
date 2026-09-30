double EaseLinear(double value) { return value; }
double EaseNone(double value) { return 0; }
double EaseInBack(double value);
double EaseInCirc(double value);
double EaseInCubic(double value);
double EaseInElastic(double value);
double EaseInExpo(double value);
double EaseInOutBack(double value);
double EaseInOutCirc(double value);
double EaseInOutCubic(double value);
double EaseInOutElastic(double value);
double EaseInOutExpo(double value);
double EaseInOutQuad(double value);
double EaseInOutQuart(double value);
double EaseInOutQuint(double value);
double EaseInOutSine(double value);
double EaseInQuad(double value);
double EaseInQuart(double value);
double EaseInQuint(double value);
double EaseInSine(double value);
double EaseOutBack(double value);
double EaseOutCirc(double value);
double EaseOutCubic(double value);
double EaseOutElastic(double value);
double EaseOutExpo(double value);
double EaseOutInBack(double value);
double EaseOutInCirc(double value);
double EaseOutInCubic(double value);
double EaseOutInElastic(double value);
double EaseOutInExpo(double value);
double EaseOutInQuad(double value);
double EaseOutInQuart(double value);
double EaseOutInQuint(double value);
double EaseOutInSine(double value);
double EaseOutQuad(double value);
double EaseOutQuart(double value);
double EaseOutQuint(double value);
double EaseOutSine(double value);
map<string, function<double(double)> > easeFunc = {
    { "linear", EaseLinear },
    { "none", EaseNone },
    { "inBack", EaseInBack },
    { "inCirc", EaseInCirc },
    { "inCubic", EaseInCubic },
    { "inElastic", EaseInElastic },
    { "inExpo", EaseInExpo },
    { "inOutBack", EaseInOutBack },
    { "inOutCirc", EaseInOutCirc },
    { "inOutCubic", EaseInOutCubic },
    { "inOutElastic", EaseInOutElastic },
    { "inOutExpo", EaseInOutExpo },
    { "inOutQuad", EaseInOutQuad },
    { "inOutQuart", EaseInOutQuart },
    { "inOutQuint", EaseInOutQuint },
    { "inOutSine", EaseInOutSine },
    { "inQuad", EaseInQuad },
    { "inQuart", EaseInQuart },
    { "inQuint", EaseInQuint },
    { "inSine", EaseInSine },
    { "outBack", EaseOutBack },
    { "outCirc", EaseOutCirc },
    { "outCubic", EaseOutCubic },
    { "outElastic", EaseOutElastic },
    { "outExpo", EaseOutExpo },
    { "outInBack", EaseOutInBack },
    { "outInCirc", EaseOutInCirc },
    { "outInCubic", EaseOutInCubic },
    { "outInElastic", EaseOutInElastic },
    { "outInExpo", EaseOutInExpo },
    { "outInQuad", EaseOutInQuad },
    { "outInQuart", EaseOutInQuart },
    { "outInQuint", EaseOutInQuint },
    { "outInSine", EaseOutInSine },
    { "outQuad", EaseOutQuad },
    { "outQuart", EaseOutQuart },
    { "outQuint", EaseOutQuint },
    { "outSine", EaseOutSine },
};

class ParticleDataEffect {
    struct Expression {
        double PI = acos(-1);
        double c = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, x3 = 0, y3 = 0, x4 = 0, y4 = 0;
        double r1 = 0, r2 = 0, r3 = 0, r4 = 0, r5 = 0, r6 = 0, r7 = 0, r8 = 0;
        double cosr1 = 0, cosr2 = 0, cosr3 = 0, cosr4 = 0, cosr5 = 0, cosr6 = 0, cosr7 = 0, cosr8 = 0;
        double sinr1 = 0, sinr2 = 0, sinr3 = 0, sinr4 = 0, sinr5 = 0, sinr6 = 0, sinr7 = 0, sinr8 = 0;

        Expression(){}
        Expression(Json::Value obj) {
            if (obj.isMember("c")) c = obj["c"].asDouble();
            if (obj.isMember("x1")) x1 = obj["x1"].asDouble();
            if (obj.isMember("y1")) y1 = obj["y1"].asDouble();
            if (obj.isMember("x2")) x2 = obj["x2"].asDouble();
            if (obj.isMember("y2")) y2 = obj["y2"].asDouble();
            if (obj.isMember("x3")) x3 = obj["x3"].asDouble();
            if (obj.isMember("y3")) y3 = obj["y3"].asDouble();
            if (obj.isMember("x4")) x4 = obj["x4"].asDouble();
            if (obj.isMember("y4")) y4 = obj["y4"].asDouble();
            if (obj.isMember("r1")) r1 = obj["r1"].asDouble();
            if (obj.isMember("r2")) r2 = obj["r2"].asDouble();
            if (obj.isMember("r3")) r3 = obj["r3"].asDouble();
            if (obj.isMember("r4")) r4 = obj["r4"].asDouble();
            if (obj.isMember("r5")) r5 = obj["r5"].asDouble();
            if (obj.isMember("r6")) r6 = obj["r6"].asDouble();
            if (obj.isMember("r7")) r7 = obj["r7"].asDouble();
            if (obj.isMember("r8")) r8 = obj["r8"].asDouble();
            if (obj.isMember("cosr1")) cosr1 = obj["cosr1"].asDouble();
            if (obj.isMember("cosr2")) cosr2 = obj["cosr2"].asDouble();
            if (obj.isMember("cosr3")) cosr3 = obj["cosr3"].asDouble();
            if (obj.isMember("cosr4")) cosr4 = obj["cosr4"].asDouble();
            if (obj.isMember("cosr5")) cosr5 = obj["cosr5"].asDouble();
            if (obj.isMember("cosr6")) cosr6 = obj["cosr6"].asDouble();
            if (obj.isMember("cosr7")) cosr7 = obj["cosr7"].asDouble();
            if (obj.isMember("cosr8")) cosr8 = obj["cosr8"].asDouble();
            if (obj.isMember("sinr1")) sinr1 = obj["sinr1"].asDouble();
            if (obj.isMember("sinr2")) sinr2 = obj["sinr2"].asDouble();
            if (obj.isMember("sinr3")) sinr3 = obj["sinr3"].asDouble();
            if (obj.isMember("sinr4")) sinr4 = obj["sinr4"].asDouble();
            if (obj.isMember("sinr5")) sinr5 = obj["sinr5"].asDouble();
            if (obj.isMember("sinr6")) sinr6 = obj["sinr6"].asDouble();
            if (obj.isMember("sinr7")) sinr7 = obj["sinr7"].asDouble();
            if (obj.isMember("sinr8")) sinr8 = obj["sinr8"].asDouble();
        }

        double calc(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double r1, double r2, double r3, double r4, double r5, double r6, double r7, double r8) const {
            return c + 
                   this->x1 * x1 + this->y1 * y1 + this->x2 * x2 + this->y2 * y2 + this->x3 * x3 + this->y3 * y3 + this->x4 * x4 + this->y4 * y4 +
                   this->r1 * r1 + this->r2 * r2 + this->r3 * r3 + this->r4 * r4 + this->r5 * r5 + this->r6 * r6 + this->r7 * r7 + this->r8 * r8 + 
                   this->cosr1 * cos(2 * PI * r1) + this->cosr2 * cos(2 * PI * r2) + this->cosr3 * cos(2 * PI * r3) + this->cosr4 * cos(2 * PI * r4) + 
                   this->cosr5 * cos(2 * PI * r5) + this->cosr6 * cos(2 * PI * r6) + this->cosr7 * cos(2 * PI * r7) + this->cosr8 * cos(2 * PI * r8) + 
                   this->sinr1 * sin(2 * PI * r1) + this->sinr2 * sin(2 * PI * r2) + this->sinr3 * sin(2 * PI * r3) + this->sinr4 * sin(2 * PI * r4) + 
                   this->sinr5 * sin(2 * PI * r5) + this->sinr6 * sin(2 * PI * r6) + this->sinr7 * sin(2 * PI * r7) + this->sinr8 * sin(2 * PI * r8);
        }
    };

    struct Particle {
        struct Property {
            Expression from, to;
            string ease;

            float getValue(double time, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double r1, double r2, double r3, double r4, double r5, double r6, double r7, double r8) const {
                double e = easeFunc[ease](time);
                double start = from.calc(x1, y1, x2, y2, x3, y3, x4, y4, r1, r2, r3, r4, r5, r6, r7, r8);
                double end = to.calc(x1, y1, x2, y2, x3, y3, x4, y4, r1, r2, r3, r4, r5, r6, r7, r8);
                return (end - start) * e + start;
            }
        };
        int sprite;
        float r, g, b;
        double start, duration;
        Property x, y, w, h, rot, a;
    };

    struct Group {
        int count;
        vector<Particle> particles;
        vector<double> r[8];
    };

    int getDec(char ch) const {
        if ('0' <= ch && ch <= '9') return ch - '0';
        else if ('A' <= ch && ch <= 'F') return ch - 'A' + 10;
        else if ('a' <= ch && ch <= 'f') return ch - 'a' + 10;
        else return 0;
    }
    void getColor(string str, float &r, float &g, float &b) const {
        assert(str[0] == '#');
        if (str.size() == 4) {
            r = 1.0 * getDec(str[1]) / 15;
            g = 1.0 * getDec(str[2]) / 15;
            b = 1.0 * getDec(str[3]) / 15;
        } else if (str.size() == 7) {
            r = 1.0 * (getDec(str[1]) * 16 + getDec(str[2])) / 255;
            g = 1.0 * (getDec(str[3]) * 16 + getDec(str[4])) / 255;
            b = 1.0 * (getDec(str[5]) * 16 + getDec(str[6])) / 255;
        } else assert(str.size() == 4 || str.size() == 7);
    }
    void bilinear(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y, float &targetx, float &targety) const {
        x = (x + 1) / 2, y = (y + 1) / 2;
        float x5 = (x2 - x1) * y + x1, y5 = (y2 - y1) * y + y1;
        float x6 = (x3 - x4) * y + x4, y6 = (y3 - y4) * y + y4;
        targetx = (x6 - x5) * x + x5, targety = (y6 - y5) * y + y5;
    }

    struct Transform {
        Expression x1, y1, x2, y2, x3, y3, x4, y4;
    }transform;
    vector<Group> groups;

    public:
    struct DrawElement {
        int sprite;
        float x1, y1;
        float x2, y2;
        float x3, y3;
        float x4, y4;
        float r, g, b, a;
    };

    double x1, y1, x2, y2, x3, y3, x4, y4;
    double stTime, duration;
    bool loop;
    
    ParticleDataEffect(){}
    ParticleDataEffect(Json::Value obj) {
        transform.x1 = Expression(obj["transform"]["x1"]);
        transform.y1 = Expression(obj["transform"]["y1"]);
        transform.x2 = Expression(obj["transform"]["x2"]);
        transform.y2 = Expression(obj["transform"]["y2"]);
        transform.x3 = Expression(obj["transform"]["x3"]);
        transform.y3 = Expression(obj["transform"]["y3"]);
        transform.x4 = Expression(obj["transform"]["x4"]);
        transform.y4 = Expression(obj["transform"]["y4"]);

        for (int i = 0; i < obj["groups"].size(); i++) {
            const Json::Value &g = obj["groups"][i];
            Group group;
            group.count = g["count"].asInt();
            for (int j = 0; j < g["particles"].size(); j++) {
                const Json::Value &p = g["particles"][j];
                Particle particle;
                particle.sprite = p["sprite"].asInt();
                getColor(p["color"].asString(), particle.r, particle.g, particle.b);
                particle.start = p["start"].asDouble();
                particle.duration = p["duration"].asDouble();
                particle.x.from = Expression(p["x"]["from"]);
                particle.x.to = Expression(p["x"]["to"]);
                particle.x.ease = p["x"]["ease"].asString();
                particle.y.from = Expression(p["y"]["from"]);
                particle.y.to = Expression(p["y"]["to"]);
                particle.y.ease = p["y"]["ease"].asString();
                particle.w.from = Expression(p["w"]["from"]);
                particle.w.to = Expression(p["w"]["to"]);
                particle.w.ease = p["w"]["ease"].asString();
                particle.h.from = Expression(p["h"]["from"]);
                particle.h.to = Expression(p["h"]["to"]);
                particle.h.ease = p["h"]["ease"].asString();
                particle.rot.from = Expression(p["r"]["from"]);
                particle.rot.to = Expression(p["r"]["to"]);
                particle.rot.ease = p["r"]["ease"].asString();
                particle.a.from = Expression(p["a"]["from"]);
                particle.a.to = Expression(p["a"]["to"]);
                particle.a.ease = p["a"]["ease"].asString();
                group.particles.push_back(particle);
            }
            groups.push_back(group);
        }
    }

    void freshVariable() {
        for (int i = 0; i < groups.size(); i++) for (int j = 0; j < 8; j++) {
            groups[i].r[j].clear();
            for (int k = 0; k < groups[i].count; k++) groups[i].r[j].push_back(1.0 * rand() / (RAND_MAX - 1));
        }
    }

    vector<DrawElement> getDrawLists(double currTime) const {
        vector<DrawElement> drawLists;
        double time = (currTime - stTime) / duration;
        time -= int(time);
        for (int i = 0; i < groups.size(); i++) {
            const Group &g = groups[i];
            for (int j = 0; j < g.count; j++) {
                double r1 = g.r[0][j], r2 = g.r[1][j], r3 = g.r[2][j], r4 = g.r[3][j];
                double r5 = g.r[4][j], r6 = g.r[5][j], r7 = g.r[6][j], r8 = g.r[7][j];
                // cout << r1 << " " << r2 << " " << r3 << " " << r4 << " " << r5 << " " << r6 << " " << r7 << " " << r8 << endl;
                for (int k = 0; k < g.particles.size(); k++) {
                    const Particle &p = g.particles[k];
                    if (time < p.start || time > p.start + p.duration) continue;
                    DrawElement e;
                    e.sprite = p.sprite;
                    e.r = p.r, e.g = p.g, e.b = p.b;
                    double newtime = (time - p.start) / p.duration;
                    float x = p.x.getValue(newtime, x1, y1, x2, y2, x3, y3, x4, y4, r1, r2, r3, r4, r5, r6, r7, r8);
                    float y = p.y.getValue(newtime, x1, y1, x2, y2, x3, y3, x4, y4, r1, r2, r3, r4, r5, r6, r7, r8);
                    float w = p.w.getValue(newtime, x1, y1, x2, y2, x3, y3, x4, y4, r1, r2, r3, r4, r5, r6, r7, r8);
                    float h = p.h.getValue(newtime, x1, y1, x2, y2, x3, y3, x4, y4, r1, r2, r3, r4, r5, r6, r7, r8);
                    float r = p.rot.getValue(newtime, x1, y1, x2, y2, x3, y3, x4, y4, r1, r2, r3, r4, r5, r6, r7, r8);
                    float a = p.a.getValue(newtime, x1, y1, x2, y2, x3, y3, x4, y4, r1, r2, r3, r4, r5, r6, r7, r8);
                    e.a = a;
                    float cx = x, cy = y;
                    float wdx = w * cos(r), wdy = w * -sin(r);
                    float hdx = h * sin(r), hdy = h * cos(r);
                    e.x1 = cx - wdx - hdx, e.y1 = cy - wdy - hdy;
                    e.x2 = cx - wdx + hdx, e.y2 = cy - wdy + hdy;
                    e.x3 = cx + wdx + hdx, e.y3 = cy + wdy + hdy;
                    e.x4 = cx + wdx - hdx, e.y4 = cy + wdy - hdy;
                    bilinear(x1, y1, x2, y2, x3, y3, x4, y4, e.x1, e.y1, e.x1, e.y1);
                    bilinear(x1, y1, x2, y2, x3, y3, x4, y4, e.x2, e.y2, e.x2, e.y2);
                    bilinear(x1, y1, x2, y2, x3, y3, x4, y4, e.x3, e.y3, e.x3, e.y3);
                    bilinear(x1, y1, x2, y2, x3, y3, x4, y4, e.x4, e.y4, e.x4, e.y4);
                    drawLists.push_back(e);
                }
            }
        }
        return drawLists;
    }
};