#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QKeyEvent>
#include <QTimer>
#include <QList>

class GameWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void updateMovement();
    void updateIdle();
    void updateWizardIdle();


private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *player;

    QPixmap walkSheet;
    QPixmap idleSheet;

    int frameIndex;
    int idleFrameIndex;
    QTimer *moveTimer;
    QTimer *idleTimer;

    enum Direction { None, Up, Down, Left, Right };
    Direction currentDirection;

    QList<QGraphicsItem*> bloqueadores;
    bool colisionaConBloqueadores(QGraphicsItem *item, qreal dx, qreal dy);

    QGraphicsPixmapItem *wizard;
    QPixmap wizardIdleSheet;
    QTimer *wizardIdleTimer;
    int wizardIdleFrameIndex;

    void checkWizardInteraction();
    void checkSlimeInteraction();


    void cambiarAMundoNuevo();

    bool mundoCambiado;
    int playerSpeed;

    QGraphicsPixmapItem *slime;
    QPixmap slimeWalkSheet;
    int slimeFrameIndex;
    QTimer *slimeTimer;
    qreal slimeDx;
    void updateSlime();
    qreal slimeDy;


    QStringList dialogoWizard;
    int fraseActualWizard = 0;
    bool dialogoActivo = false;
    QGraphicsRectItem *dialogoCaja = nullptr;
    QGraphicsTextItem *dialogoTexto = nullptr;
    QGraphicsTextItem *dialogoAyuda;

    QGraphicsTextItem *labelMago;
    QGraphicsTextItem *labelSlime;


    QTimer *timerTextoWizard = nullptr;
    int letraActualWizard = 0;
    QString textoParcialWizard;
    void updateLetraWizard();


    // Diálogo del segundo mapa
    QStringList dialogoSegundoMapa;
    int fraseActualSegundoMapa = 0;

    QTimer *timerTextoSegundoMapa = nullptr;
    QString textoParcialSegundoMapa;
    int letraActualSegundoMapa = 0;

    // Función de letra a letra
    void updateLetraSegundoMapa();

    // Armored Axeman (NPC)
    QGraphicsPixmapItem *axeman = nullptr;
    QPixmap axemanIdleSheet;
    int axemanIdleFrameIndex = 0;
    QTimer *axemanIdleTimer = nullptr;

    void updateAxemanIdle();



};

#endif // GAMEWINDOW_H
