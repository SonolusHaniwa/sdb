class SpriteTransform {
    struct TransformSingle {
        double x1, x2, x3, x4;
        double y1, y2, y3, y4;
    };
    TransformSingle x1{ .x1 = 1 };
    TransformSingle x2{ .x2 = 1 };
    TransformSingle x3{ .x3 = 1 };
    TransformSingle x4{ .x4 = 1 };
    TransformSingle y1{ .y1 = 1 };
    TransformSingle y2{ .y2 = 1 };
    TransformSingle y3{ .y3 = 1 };
    TransformSingle y4{ .y4 = 1 };

    void setSingle(TransformSingle &t, const Json::Value &obj) {
        if (obj.isMember("x1")) t.x1 = obj["x1"].asDouble();
        if (obj.isMember("x2")) t.x2 = obj["x2"].asDouble();
        if (obj.isMember("x3")) t.x3 = obj["x3"].asDouble();
        if (obj.isMember("x4")) t.x4 = obj["x4"].asDouble();
        if (obj.isMember("y1")) t.y1 = obj["y1"].asDouble();
        if (obj.isMember("y2")) t.y2 = obj["y2"].asDouble();
        if (obj.isMember("y3")) t.y3 = obj["y3"].asDouble();
        if (obj.isMember("y4")) t.y4 = obj["y4"].asDouble();
    }

    double calcSingle(const TransformSingle &t, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
        return t.x1 * x1 + t.y1 * y1 + t.x2 * x2 + t.y2 * y2 + t.x3 * x3 + t.y3 * y3 + t.x4 * x4 + t.y4 * y4;
    }

    public:
    SpriteTransform(){}
    SpriteTransform(const Json::Value &obj) {
        if (obj.isMember("x1")) setSingle(x1, obj["x1"]);
        if (obj.isMember("x2")) setSingle(x2, obj["x2"]);
        if (obj.isMember("x3")) setSingle(x3, obj["x3"]);
        if (obj.isMember("x4")) setSingle(x4, obj["x4"]);
        if (obj.isMember("y1")) setSingle(y1, obj["y1"]);
        if (obj.isMember("y2")) setSingle(y2, obj["y2"]);
        if (obj.isMember("y3")) setSingle(y3, obj["y3"]);
        if (obj.isMember("y4")) setSingle(y4, obj["y4"]);
    }

    void calc(double &x1, double &y1, double &x2, double &y2, double &x3, double &y3, double &x4, double &y4) {
        double newx1 = calcSingle(this->x1, x1, y1, x2, y2, x3, y3, x4, y4);
        double newx2 = calcSingle(this->x2, x1, y1, x2, y2, x3, y3, x4, y4);
        double newx3 = calcSingle(this->x3, x1, y1, x2, y2, x3, y3, x4, y4);
        double newx4 = calcSingle(this->x4, x1, y1, x2, y2, x3, y3, x4, y4);
        double newy1 = calcSingle(this->y1, x1, y1, x2, y2, x3, y3, x4, y4);
        double newy2 = calcSingle(this->y2, x1, y1, x2, y2, x3, y3, x4, y4);
        double newy3 = calcSingle(this->y3, x1, y1, x2, y2, x3, y3, x4, y4);
        double newy4 = calcSingle(this->y4, x1, y1, x2, y2, x3, y3, x4, y4);
        x1 = newx1, x2 = newx2, x3 = newx3, x4 = newx4;
        y1 = newy1, y2 = newy2, y3 = newy3, y4 = newy4;
    }
};