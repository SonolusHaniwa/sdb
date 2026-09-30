template<int m, int n, typename T>
std::ostream &operator << (std::ostream &out, const glm::mat<m, n, T> &mat) {
    out << "[" << std::endl;
    for (int i = 0; i < m; i++) {
        out << "    [";
        for (int j = 0; j < n; j++) out << (j ? ", " : "") << mat[i][j];
        out << "]" << (i == m - 1 ? "" : ",") << std::endl;
    }
    out << "]";
    return out;
}

template<int m, typename T>
std::ostream &operator << (std::ostream &out, const glm::vec<m, T> &vec) {
    out << "[";
    for (int i = 0; i < m; i++) out << (i ? ", " : "") << vec[i];
    out << "]";
    return out;
}

time_t clock2() {
	return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count();
}