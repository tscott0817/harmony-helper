#ifndef GUITAR_APP_OBJECTHANDLER_H
#define GUITAR_APP_OBJECTHANDLER_H


class objectHandler {

private:
    std::vector<std::shared_ptr<modal_chart>> modalCharts;

public:

    objectHandler();
    ~objectHandler();

    void drawObjects();
    void updateObjects();



};


#endif //GUITAR_APP_OBJECTHANDLER_H
