struct Touch {
    bool started, ended;
    double t, st;
    double x, y;
    double sx, sy;
    double dx, dy;
    double vx, vy, vr, vw;
};

map<int, Touch> touches;
int touchCount = 0;

int createTouch(double time, double x, double y) {
    Touch touch;
    touch.started = true, touch.ended = false;
    touch.t = touch.st = time;
    touch.x = x, touch.y = y;
    touch.sx = x, touch.sy = y;
    touch.dx = touch.dy = 0;
    touch.vx = touch.vy = touch.vr = touch.vw = 0;
    int id = ++touchCount;
    touches[id] = touch;
    return id;
}

void updateTouch(int id, double time, double x, double y) {
    if (touches.count(id) == 0) return;
    Touch touch = touches[id], t = touch;
    if (time == touch.t) return;
    t.started = false, t.ended = false;
    t.t = time;
    t.x = x, t.y = y;
    t.dx = x - touch.x, t.dy = y - touch.y;
    t.vx = t.dx / (t.t - touch.t), t.vy = t.dy / (t.t - touch.t);
    t.vr = atan2(t.dy, t.dx), t.vw = sqrt(t.dx * t.dx + t.dy * t.dy);
    touches[id] = t;
}

void removeTouch(int id, double time, double x, double y) {
    if (touches.count(id) == 0) return;
    Touch touch = touches[id], t = touch;
    t.started = false, t.ended = true;
    t.t = time;
    t.x = x, t.y = y;
    t.dx = x - touch.x, t.dy = y - touch.y;
    t.vx = t.dx / (t.t - touch.t), t.vy = t.dy / (t.t - touch.t);
    t.vr = atan2(t.dy, t.dx), t.vw = sqrt(t.dx * t.dx + t.dy * t.dy);
    touches[id] = t;
}

void clearTouch() {
    for (auto it = touches.begin(); it != touches.end(); ) {
        if (it->second.ended) it = touches.erase(it);
        else it++;
    }
}

void freshTouch(double time) {
    for (auto it = touches.begin(); it != touches.end(); it++) {
        if (time != it->second.t) {
            updateTouch(it->first, time, it->second.x, it->second.y);
        }
    }
}