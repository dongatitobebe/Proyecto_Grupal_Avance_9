#include "GameWindow.h"
#include <QMessageBox>



GameWindow::GameWindow(QWidget *parent)
    : QDialog(parent), frameIndex(0), currentDirection(None), idleFrameIndex(0)
{
    this->setWindowTitle("Mapa del Juego");

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    // Cargar mapa
    QPixmap mapa("C:/Users/Tomas Yuja/OneDrive/Escritorio/Proyecto_II_Q2/map1.png");

    if (mapa.isNull()) {
        qDebug("Error: No se pudo cargar el mapa.");
    } else {
        scene->addPixmap(mapa);

        this->resize(mapa.width(), mapa.height());
        view->setGeometry(0, 0, mapa.width(), mapa.height());
        view->resetTransform();
        view->scale(1.0, 1.0);

    }

    // ------------------------------------------Caballero ----------------------------------------------------------------------------------
    // Cargar Knight-Walk
    walkSheet = QPixmap("C:/Users/Tomas Yuja/OneDrive/Escritorio/Proyecto_II_Q2/Knight-Walk.png");
    if (walkSheet.isNull()) {
        qDebug("Error: No se pudo cargar el Knight-Walk.");
    }

    // Cargar Knight-Idle
    idleSheet = QPixmap("C:/Users/Tomas Yuja/OneDrive/Escritorio/Proyecto_II_Q2/Knight-Idle.png");
    if (idleSheet.isNull()) {
        qDebug("Error: No se pudo cargar el Knight-Idle.");
    }

    if (!idleSheet.isNull()) {
        QPixmap frame = idleSheet.copy(0, 0, 100, 100);
        player = scene->addPixmap(frame);
        player->setPos(110, 200);
    }

    // Crear Timer de movimiento
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &GameWindow::updateMovement);

    // Crear Timer de Idle
    idleTimer = new QTimer(this);
    connect(idleTimer, &QTimer::timeout, this, &GameWindow::updateIdle);
    mundoCambiado = false;
    playerSpeed = 5;


    //------------------------------------------------- colisiones villac++ --------------------------------------------------------
    QGraphicsRectItem *bloque = scene->addRect(1, 1, 334, 127);
    bloque->setBrush(Qt::transparent);
    bloque->setPen(Qt::NoPen);
    bloqueadores.append(bloque);

    QGraphicsRectItem *bloque2 = scene->addRect(70, 200, 29, 29);
    bloque2->setBrush(Qt::transparent);
    bloque2->setPen(Qt::NoPen);
    bloqueadores.append(bloque2);

    QGraphicsRectItem *bloque3 = scene->addRect(44, 136, 44, 10);
    bloque3->setBrush(Qt::transparent);
    bloque3->setPen(Qt::NoPen);
    bloqueadores.append(bloque3);

    QGraphicsRectItem *bloque4 = scene->addRect(29, 156, 23, 22);
    bloque4->setBrush(Qt::transparent);
    bloque4->setPen(Qt::NoPen);
    bloqueadores.append(bloque4);

    QGraphicsRectItem *bloque5 = scene->addRect(24, 180, 10, 75);
    bloque5->setBrush(Qt::transparent);
    bloque5->setPen(Qt::NoPen);
    bloqueadores.append(bloque5);

    QGraphicsRectItem *bloque6 = scene->addRect(9, 265, 11, 48);
    bloque6->setBrush(Qt::transparent);
    bloque6->setPen(Qt::NoPen);
    bloqueadores.append(bloque6);

    QGraphicsRectItem *bloque7 = scene->addRect(26, 316, 11, 49);
    bloque7->setBrush(Qt::transparent);
    bloque7->setPen(Qt::NoPen);
    bloqueadores.append(bloque7);

    QGraphicsRectItem *bloque8 = scene->addRect(43, 348, 11, 50);
    bloque8->setBrush(Qt::transparent);
    bloque8->setPen(Qt::NoPen);
    bloqueadores.append(bloque8);

    QGraphicsRectItem *bloque9 = scene->addRect(55, 396, 30, 50);
    bloque9->setBrush(Qt::transparent);
    bloque9->setPen(Qt::NoPen);
    bloqueadores.append(bloque9);

    QGraphicsRectItem *bloque10 = scene->addRect(85, 412, 17, 38);
    bloque10->setBrush(Qt::transparent);
    bloque10->setPen(Qt::NoPen);
    bloqueadores.append(bloque10);

    QGraphicsRectItem *bloque11 = scene->addRect(52, 450, 17, 19);
    bloque11->setBrush(Qt::transparent);
    bloque11->setPen(Qt::NoPen);
    bloqueadores.append(bloque11);

    QGraphicsRectItem *bloque12 = scene->addRect(35, 478, 17, 19);
    bloque12->setBrush(Qt::transparent);
    bloque12->setPen(Qt::NoPen);
    bloqueadores.append(bloque12);

    QGraphicsRectItem *bloque13 = scene->addRect(17, 497, 17, 16);
    bloque13->setBrush(Qt::transparent);
    bloque13->setPen(Qt::NoPen);
    bloqueadores.append(bloque13);

    QGraphicsRectItem *bloque14 = scene->addRect(8, 518, 11, 72);
    bloque14->setBrush(Qt::transparent);
    bloque14->setPen(Qt::NoPen);
    bloqueadores.append(bloque14);

    QGraphicsRectItem *bloque15 = scene->addRect(21, 586, 16, 16);
    bloque15->setBrush(Qt::transparent);
    bloque15->setPen(Qt::NoPen);
    bloqueadores.append(bloque15);

    QGraphicsRectItem *bloque16 = scene->addRect(46, 600, 25, 16);
    bloque16->setBrush(Qt::transparent);
    bloque16->setPen(Qt::NoPen);
    bloqueadores.append(bloque16);

    QGraphicsRectItem *bloque17 = scene->addRect(74, 615, 60, 16);
    bloque17->setBrush(Qt::transparent);
    bloque17->setPen(Qt::NoPen);
    bloqueadores.append(bloque17);

    QGraphicsRectItem *bloque18 = scene->addRect(133, 631, 95, 14);
    bloque18->setBrush(Qt::transparent);
    bloque18->setPen(Qt::NoPen);
    bloqueadores.append(bloque18);

    QGraphicsRectItem *bloque19 = scene->addRect(225, 613, 26, 14);
    bloque19->setBrush(Qt::transparent);
    bloque19->setPen(Qt::NoPen);
    bloqueadores.append(bloque19);

    QGraphicsRectItem *bloque20 = scene->addRect(242, 598, 26, 14);
    bloque20->setBrush(Qt::transparent);
    bloque20->setPen(Qt::NoPen);
    bloqueadores.append(bloque20);

    QGraphicsRectItem *bloque21 = scene->addRect(255, 569, 26, 23);
    bloque21->setBrush(Qt::transparent);
    bloque21->setPen(Qt::NoPen);
    bloqueadores.append(bloque21);

    QGraphicsRectItem *bloque22 = scene->addRect(275, 550, 26, 23);
    bloque22->setBrush(Qt::transparent);
    bloque22->setPen(Qt::NoPen);
    bloqueadores.append(bloque22);

    QGraphicsRectItem *bloque23 = scene->addRect(290, 519, 26, 23);
    bloque23->setBrush(Qt::transparent);
    bloque23->setPen(Qt::NoPen);
    bloqueadores.append(bloque23);

    QGraphicsRectItem *bloque24 = scene->addRect(306, 483, 26, 31);
    bloque24->setBrush(Qt::transparent);
    bloque24->setPen(Qt::NoPen);
    bloqueadores.append(bloque24);

    QGraphicsRectItem *bloque25 = scene->addRect(320, 316, 8, 184);
    bloque25->setBrush(Qt::transparent);
    bloque25->setPen(Qt::NoPen);
    bloqueadores.append(bloque25);

    QGraphicsRectItem *bloque26 = scene->addRect(301, 189, 8, 136);
    bloque26->setBrush(Qt::transparent);
    bloque26->setPen(Qt::NoPen);
    bloqueadores.append(bloque26);

    QGraphicsRectItem *bloque27 = scene->addRect(286, 199, 8, 18);
    bloque27->setBrush(Qt::transparent);
    bloque27->setPen(Qt::NoPen);
    bloqueadores.append(bloque27);

    QGraphicsRectItem *bloque28 = scene->addRect(270, 179, 16, 17);
    bloque28->setBrush(Qt::transparent);
    bloque28->setPen(Qt::NoPen);
    bloqueadores.append(bloque28);

    QGraphicsRectItem *bloque29 = scene->addRect(240, 163, 23, 17);
    bloque29->setBrush(Qt::transparent);
    bloque29->setPen(Qt::NoPen);
    bloqueadores.append(bloque29);

    QGraphicsRectItem *bloque30 = scene->addRect(208, 134, 24, 30);
    bloque30->setBrush(Qt::transparent);
    bloque30->setPen(Qt::NoPen);
    bloqueadores.append(bloque30);

    QGraphicsRectItem *bloque31 = scene->addRect(273, 364, 16, 22);
    bloque31->setBrush(Qt::transparent);
    bloque31->setPen(Qt::NoPen);
    bloqueadores.append(bloque31);

    QGraphicsRectItem *bloque32 = scene->addRect(137, 281, 40, 71);
    bloque32->setBrush(Qt::transparent);
    bloque32->setPen(Qt::NoPen);
    bloqueadores.append(bloque32);

    QGraphicsRectItem *bloque33 = scene->addRect(164, 284, 16, 68);
    bloque33->setBrush(Qt::transparent);
    bloque33->setPen(Qt::NoPen);
    bloqueadores.append(bloque33);

    QGraphicsRectItem *bloque34 = scene->addRect(184, 305, 16, 47);
    bloque34->setBrush(Qt::transparent);
    bloque34->setPen(Qt::NoPen);
    bloqueadores.append(bloque34);

    QGraphicsRectItem *bloque35 = scene->addRect(193, 315, 20, 38);
    bloque35->setBrush(Qt::transparent);
    bloque35->setPen(Qt::NoPen);
    bloqueadores.append(bloque35);

    QGraphicsRectItem *bloque36 = scene->addRect(206, 326, 19, 27);
    bloque36->setBrush(Qt::transparent);
    bloque36->setPen(Qt::NoPen);
    bloqueadores.append(bloque36);


    QGraphicsRectItem *bloque37 = scene->addRect(174, 346, 19, 27);
    bloque37->setBrush(Qt::transparent);
    bloque37->setPen(Qt::NoPen);
    bloqueadores.append(bloque37);

    QGraphicsRectItem *bloque38 = scene->addRect(188, 359, 37, 18);
    bloque38->setBrush(Qt::transparent);
    bloque38->setPen(Qt::NoPen);
    bloqueadores.append(bloque38);

    QGraphicsRectItem *bloque39 = scene->addRect(79, 286, 20, 29);
    bloque39->setBrush(Qt::transparent);
    bloque39->setPen(Qt::NoPen);
    bloqueadores.append(bloque39);

    QGraphicsRectItem *bloque40 = scene->addRect(227, 223, 2, 30);
    bloque40->setBrush(Qt::transparent);
    bloque40->setPen(Qt::NoPen);
    bloqueadores.append(bloque40);

    QGraphicsRectItem *bloque41 = scene->addRect(187, 223, 2, 29);
    bloque41->setBrush(Qt::transparent);
    bloque41->setPen(Qt::NoPen);
    bloqueadores.append(bloque41);

    QGraphicsRectItem *bloque42 = scene->addRect(187, 225, 42, 1);
    bloque42->setBrush(Qt::transparent);
    bloque42->setPen(Qt::NoPen);
    bloqueadores.append(bloque42);

    QGraphicsRectItem *bloque43 = scene->addRect(225, 414, 4, 8);
    bloque43->setBrush(Qt::transparent);
    bloque43->setPen(Qt::NoPen);
    bloqueadores.append(bloque43);

    QGraphicsRectItem *bloque44 = scene->addRect(145, 458, 34, 40);
    bloque44->setBrush(Qt::transparent);
    bloque44->setPen(Qt::NoPen);
    bloqueadores.append(bloque44);

    QGraphicsRectItem *bloque45 = scene->addRect(148, 498, 17, 64);
    bloque45->setBrush(Qt::transparent);
    bloque45->setPen(Qt::NoPen);
    bloqueadores.append(bloque45);

    QGraphicsRectItem *bloque46 = scene->addRect(163, 558, 14, 29);
    bloque46->setBrush(Qt::transparent);
    bloque46->setPen(Qt::NoPen);
    bloqueadores.append(bloque46);

    QGraphicsRectItem *bloque47 = scene->addRect(130, 545, 29, 15);
    bloque47->setBrush(Qt::transparent);
    bloque47->setPen(Qt::NoPen);
    bloqueadores.append(bloque47);

    QGraphicsRectItem *bloque48 = scene->addRect(81, 532, 40, 12);
    bloque48->setBrush(Qt::transparent);
    bloque48->setPen(Qt::NoPen);
    bloqueadores.append(bloque48);

    QGraphicsRectItem *bloque49 = scene->addRect(83, 539, 12, 21);
    bloque49->setBrush(Qt::transparent);
    bloque49->setPen(Qt::NoPen);
    bloqueadores.append(bloque49);

    QGraphicsRectItem *bloque50 = scene->addRect(135, 475, 1, 38);
    bloque50->setBrush(Qt::transparent);
    bloque50->setPen(Qt::NoPen);
    bloqueadores.append(bloque50);

    QGraphicsRectItem *bloque51 = scene->addRect(122, 489, 17, 22);
    bloque51->setBrush(Qt::transparent);
    bloque51->setPen(Qt::NoPen);
    bloqueadores.append(bloque51);

    QGraphicsRectItem *bloque52 = scene->addRect(100, 506, 11, 22);
    bloque52->setBrush(Qt::transparent);
    bloque52->setPen(Qt::NoPen);
    bloqueadores.append(bloque52);

    QGraphicsRectItem *bloque53 = scene->addRect(242, 459, 15, 38);
    bloque53->setBrush(Qt::transparent);
    bloque53->setPen(Qt::NoPen);
    bloqueadores.append(bloque53);

    QGraphicsRectItem *bloque54 = scene->addRect(257, 445, 15, 34);
    bloque54->setBrush(Qt::transparent);
    bloque54->setPen(Qt::NoPen);
    bloqueadores.append(bloque54);

    //------------------------------------------------------------ Mago --------------------------------------------------------------------------------------------------

    // Cargar Wizard-Idle
    wizardIdleSheet = QPixmap("C:/Users/Tomas Yuja/OneDrive/Escritorio/Proyecto_II_Q2/Wizard-Idle.png");

    if (wizardIdleSheet.isNull()) {
        qDebug("Error: No se pudo cargar Wizard-Idle.");
    } else {
        QPixmap frame = wizardIdleSheet.copy(0, 0, 100, 100);
        wizard = scene->addPixmap(frame);

        wizard->setPos(125, 490);
        bloqueadores.append(wizard);


        wizardIdleFrameIndex = 0;
        wizardIdleTimer = new QTimer(this);
        connect(wizardIdleTimer, &QTimer::timeout, this, &GameWindow::updateWizardIdle);
        wizardIdleTimer->start(250);


    }


    // ------------------------------------------------------------ Slime (NPC) --------------------------------------------------------------------------------------------------

    slimeWalkSheet = QPixmap("C:/Users/Tomas Yuja/OneDrive/Escritorio/Proyecto_II_Q2/Slime-Walk.png");

    if (slimeWalkSheet.isNull()) {
        qDebug("Error: No se pudo cargar Slime-Walk.");
    } else {
        QPixmap frame = slimeWalkSheet.copy(0, 0, 100, 100);
        slime = scene->addPixmap(frame);

        slime->setPos(100, 100);
        slime->setZValue(1);

        slimeFrameIndex = 0;
        slimeDx = 1.0;
        slimeDy = 1.0;

        slimeTimer = new QTimer(this);
        connect(slimeTimer, &QTimer::timeout, this, &GameWindow::updateSlime);
        slimeTimer->start(270);
    }

    //  Crear label del Mago
    labelMago = scene->addText("Mago");
    labelMago->setDefaultTextColor(Qt::yellow);
    labelMago->setFont(QFont("Arial", 10, QFont::Bold));
    labelMago->setZValue(2);
    labelMago->setPos(wizard->x() + 20, wizard->y() - 20);
    labelMago->setVisible(false);

    //  Crear label del Slime
    labelSlime = scene->addText("Slime");
    labelSlime->setDefaultTextColor(Qt::green);
    labelSlime->setFont(QFont("Arial", 10, QFont::Bold));
    labelSlime->setZValue(2);
    labelSlime->setPos(slime->x() + 20, slime->y() - 20);
    labelSlime->setVisible(false);


    this->setFocus();
}

GameWindow::~GameWindow()
{
}

//----------------------------------------------------- mago -------------------------------------------------------------
void GameWindow::updateWizardIdle()
{
    if (!wizard) return;

    int frameWidth = 100;
    int frameHeight = 100;
    int idleFrames = 6;

    wizard->setPixmap(wizardIdleSheet.copy(wizardIdleFrameIndex * frameWidth, 0, frameWidth, frameHeight));

    wizardIdleFrameIndex = (wizardIdleFrameIndex + 1) % idleFrames;
}

void GameWindow::checkWizardInteraction()
{
    if (!player || !wizard) return;

    if (mundoCambiado || dialogoActivo) return;

    qreal distance = QLineF(player->scenePos(), wizard->scenePos()).length();

    if (distance < 30.0)
    {
        qDebug() << "¡Knight interactúa con el Wizard!";

        //  Pausar timers
        if (slimeTimer && slimeTimer->isActive()) {
            slimeTimer->stop();
        }

        if (moveTimer && moveTimer->isActive()) {
            moveTimer->stop();
        }

        //  Preparar las frases
        dialogoWizard.clear();
        dialogoWizard << "Mago: Hola caballero C++."
                      << "Caballero: ¿Quién eres tú?"
                      << "Mago: Yo soy un mago y debo decirte algo muy importante y todo depende de que tú me ayudes."
                      << "Caballero: Hmm... ¿y por qué yo? ¿Qué debo hacer?"
                      << "Mago: El mundo está en peligro y debemos salvarlo. En esta tierra hay una piedra llamada Éterium. "
                         "El jefe, que es un villano, destruyó la piedra en varios fragmentos. Tú debes restaurar la paz del mundo y vencer al jefe."
                      <<"Caballero: Pero no puedo hacerlo. No se como salvar al mundo. :("
                      <<" Mago: No te preocupes cuando te toque enfrentarte a un enemigo mis amigas curandera y princesa C# te van ayudar"
                         " No tengas miedo, al trabajar todos juntos podemos salvar el mundo."
                      << "Caballero: Está bien, salvaré al mundo.";

        fraseActualWizard = 0;
        dialogoActivo = true;

        //  Crear la caja de diálogo
        int margenLateral = 30;
        int margenInferior = 350;
        int altoCaja = 130;

        dialogoCaja = scene->addRect(
            margenLateral,
            scene->height() - margenInferior,
            scene->width() - 2 * margenLateral,
            altoCaja,
            QPen(Qt::NoPen),
            QBrush(QColor(40, 60, 40, 220))
            );


        //  Inicializar texto letra a letra
        textoParcialWizard = "";
        letraActualWizard = 0;

        dialogoTexto = scene->addText(textoParcialWizard);
        dialogoTexto->setDefaultTextColor(Qt::white);
        dialogoTexto->setFont(QFont("Arial", 10, QFont::Normal));
        dialogoTexto->setTextWidth(dialogoCaja->rect().width() - 30);

        int margenTextoX = 15;
        int margenTextoY = 10;

        dialogoTexto->setPos(
            margenLateral + margenTextoX,
            scene->height() - margenInferior + margenTextoY
            );



        //  Crear el texto de ayuda
        dialogoAyuda = scene->addText("[Espacio] → Siguiente");
        dialogoAyuda->setDefaultTextColor(Qt::yellow);
        dialogoAyuda->setFont(QFont("Arial", 9, QFont::Normal));

        dialogoAyuda->setPos(
            margenLateral + (scene->width() - 2 * margenLateral) - 200,
            scene->height() - margenInferior + altoCaja - 150
            );


        //  Crear el timer de letra a letra
        timerTextoWizard = new QTimer(this);
        connect(timerTextoWizard, &QTimer::timeout, this, &GameWindow::updateLetraWizard);
        timerTextoWizard->start(30);
    }
}

void GameWindow::updateLetraWizard()
{
    if (fraseActualWizard >= dialogoWizard.size())
    {
        timerTextoWizard->stop();
        return;
    }

    const QString &frase = dialogoWizard[fraseActualWizard];

    if (letraActualWizard < frase.length())
    {
        textoParcialWizard += frase[letraActualWizard];
        dialogoTexto->setPlainText(textoParcialWizard);
        letraActualWizard++;
    }
    else
    {
        timerTextoWizard->stop();
    }
}








void GameWindow::checkSlimeInteraction()
{
    if (!player || !slime) return;

    qreal distance = QLineF(player->scenePos(), slime->scenePos()).length();

    if (distance < 20.0)
    {
        qDebug() << "¡Knight ha chocado con la babosa!";

        if (slimeTimer && slimeTimer->isActive()) {
            slimeTimer->stop();
        }

        if (moveTimer && moveTimer->isActive()) {
            moveTimer->stop();
        }

        QMessageBox::information(this, "¡Enemigo!", "Oh no, te has topado con una babosa enemiga!");

        if (labelSlime) {
            scene->removeItem(labelSlime);
            delete labelSlime;
            labelSlime = nullptr;
        }

        if (slime) {
            scene->removeItem(slime);
            delete slime;
            slime = nullptr;
        }

        currentDirection = None;

        if (!idleSheet.isNull()) {
            idleFrameIndex = 0;
            idleTimer->start(250);
        }

        // El moveTimer NO se reactiva → el caballero queda quieto hasta que el jugador toque teclas
        qDebug() << "Babosa eliminada. Knight en Idle.";
    }
}






void GameWindow::cambiarAMundoNuevo()
{

    if (labelMago) {
        scene->removeItem(labelMago);
        delete labelMago;
        labelMago = nullptr;
    }

    if (labelSlime) {
        scene->removeItem(labelSlime);
        delete labelSlime;
        labelSlime = nullptr;
    }

    if (slimeTimer && slimeTimer->isActive()) {
        slimeTimer->stop();
    }

    if (slime) {
        scene->removeItem(slime);
        delete slime;
        slime = nullptr;
    }

    scene->clear();
    bloqueadores.clear();

    QPixmap nuevoMapa("C:/Users/Tomas Yuja/OneDrive/Escritorio/Proyecto_II_Q2/Scene Overview2.png");

    if (nuevoMapa.isNull()) {
        qDebug("Error: No se pudo cargar el nuevo mapa.");
        return;
    }


    QGraphicsPixmapItem *mapItem = scene->addPixmap(nuevoMapa);
    mapItem->setZValue(-1);
    scene->setSceneRect(0, 0, nuevoMapa.width(), nuevoMapa.height());
    view->setFixedSize(800, 800);
    this->setFixedSize(800, 800);


    view->resetTransform();
    view->scale(1.2, 1.2);

    // Crear Knight
    if (!idleSheet.isNull()) {
        QPixmap frame = idleSheet.copy(0, 0, 100, 100);
        player = scene->addPixmap(frame);
        player->setZValue(1);
        player->setPos(590, 1);
        view->centerOn(player);


        // ESCALAR Knight:
        player->setScale(2.0);
    }

    // Crear Wizard
    if (!wizardIdleSheet.isNull()) {
        QPixmap frame = wizardIdleSheet.copy(0, 0, 100, 100);
        wizard = scene->addPixmap(frame);
        wizard->setZValue(1);
        wizard->setPos(520, 1);

        wizard->setScale(2.0);

        bloqueadores.append(wizard);

    }

    // ------------------------------------------------------------ Armored Axeman (NPC) --------------------------------------------------------------------------------------------------

    axemanIdleSheet = QPixmap("C:/Users/Tomas Yuja/OneDrive/Escritorio/Proyecto_II_Q2/Armored Axeman-Idle.png");

    if (axemanIdleSheet.isNull()) {
        qDebug("Error: No se pudo cargar Armored Axeman-Idle.");
    } else {
        QPixmap frame = axemanIdleSheet.copy(0, 0, 100, 100);
        axeman = scene->addPixmap(frame);

        axeman->setPos(500, 600);
        axeman->setZValue(1);
        axeman->setScale(2.0);
        bloqueadores.append(axeman);

        axemanIdleFrameIndex = 0;
        axemanIdleTimer = new QTimer(this);
        connect(axemanIdleTimer, &QTimer::timeout, this, &GameWindow::updateAxemanIdle);
        axemanIdleTimer->start(250);
    }


    // colisiones exterior
    QGraphicsRectItem *bloqueNuevo1 = scene->addRect(567, 16, 213, 10);
    bloqueNuevo1->setBrush(Qt::transparent);
    bloqueNuevo1->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo1);

    QGraphicsRectItem *bloqueNuevo2 = scene->addRect(748, 34, 49, 32);
    bloqueNuevo2->setBrush(Qt::transparent);
    bloqueNuevo2->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo2);

    QGraphicsRectItem *bloqueNuevo3 = scene->addRect(783, 74, 139, 149);
    bloqueNuevo3->setBrush(Qt::transparent);
    bloqueNuevo3->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo3);

    QGraphicsRectItem *bloqueNuevo4 = scene->addRect(871, 210, 45, 52);
    bloqueNuevo4->setBrush(Qt::transparent);
    bloqueNuevo4->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo4);

    QGraphicsRectItem *bloqueNuevo5 = scene->addRect(909, 233, 45, 91);
    bloqueNuevo5->setBrush(Qt::transparent);
    bloqueNuevo5->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo5);

    QGraphicsRectItem *bloqueNuevo6 = scene->addRect(939, 295, 9, 212);
    bloqueNuevo6->setBrush(Qt::transparent);
    bloqueNuevo6->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo6);

    QGraphicsRectItem *bloqueNuevo7 = scene->addRect(957, 465, 139, 16);
    bloqueNuevo7->setBrush(Qt::transparent);
    bloqueNuevo7->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo7);

    QGraphicsRectItem *bloqueNuevo8 = scene->addRect(1075, 453, 38, 356);
    bloqueNuevo8->setBrush(Qt::transparent);
    bloqueNuevo8->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo8);

    QGraphicsRectItem *bloqueNuevo9 = scene->addRect(870, 729, 201, 193);
    bloqueNuevo9->setBrush(Qt::transparent);
    bloqueNuevo9->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo9);

    QGraphicsRectItem *bloqueNuevo10 = scene->addRect(1003, 913, 29, 192);
    bloqueNuevo10->setBrush(Qt::transparent);
    bloqueNuevo10->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo10);

    QGraphicsRectItem *bloqueNuevo11 = scene->addRect(958, 969, 30, 51);
    bloqueNuevo11->setBrush(Qt::transparent);
    bloqueNuevo11->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo11);

    QGraphicsRectItem *bloqueNuevo12 = scene->addRect(882, 1014, 123, 110);
    bloqueNuevo12->setBrush(Qt::transparent);
    bloqueNuevo12->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo12);

    QGraphicsRectItem *bloqueNuevo13 = scene->addRect(593, 1071, 300, 41);
    bloqueNuevo13->setBrush(Qt::transparent);
    bloqueNuevo13->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo13);

    QGraphicsRectItem *bloqueNuevo14 = scene->addRect(812, 1040, 13, 24);
    bloqueNuevo14->setBrush(Qt::transparent);
    bloqueNuevo14->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo14);

    QGraphicsRectItem *bloqueNuevo15 = scene->addRect(717, 1031, 13, 32);
    bloqueNuevo15->setBrush(Qt::transparent);
    bloqueNuevo15->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo15);

    QGraphicsRectItem *bloqueNuevo16 = scene->addRect(161, 1013, 443, 128);
    bloqueNuevo16->setBrush(Qt::transparent);
    bloqueNuevo16->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo16);

    QGraphicsRectItem *bloqueNuevo17 = scene->addRect(162, 806, 55, 296);
    bloqueNuevo17->setBrush(Qt::transparent);
    bloqueNuevo17->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo17);

    QGraphicsRectItem *bloqueNuevo18 = scene->addRect(212, 972, 43, 42);
    bloqueNuevo18->setBrush(Qt::transparent);
    bloqueNuevo18->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo18);

    QGraphicsRectItem *bloqueNuevo19 = scene->addRect(115, 661, 169, 229);
    bloqueNuevo19->setBrush(Qt::transparent);
    bloqueNuevo19->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo19);

    QGraphicsRectItem *bloqueNuevo20 = scene->addRect(136, 416, 25, 323);
    bloqueNuevo20->setBrush(Qt::transparent);
    bloqueNuevo20->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo20);

    QGraphicsRectItem *bloqueNuevo21 = scene->addRect(136, 271, 150, 188);
    bloqueNuevo21->setBrush(Qt::transparent);
    bloqueNuevo21->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo21);

    QGraphicsRectItem *bloqueNuevo22 = scene->addRect(289, 232, 26, 162);
    bloqueNuevo22->setBrush(Qt::transparent);
    bloqueNuevo22->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo22);

    QGraphicsRectItem *bloqueNuevo23 = scene->addRect(319, 94, 90, 150);
    bloqueNuevo23->setBrush(Qt::transparent);
    bloqueNuevo23->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo23);


    QGraphicsRectItem *bloqueNuevo24 = scene->addRect(396, 42, 171, 82);
    bloqueNuevo24->setBrush(Qt::transparent);
    bloqueNuevo24->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo24);

    QGraphicsRectItem *bloqueNuevo25 = scene->addRect(554, 35, 53, 36);
    bloqueNuevo25->setBrush(Qt::transparent);
    bloqueNuevo25->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo25);

    //colisiones internas
    QGraphicsRectItem *bloqueNuevo26 = scene->addRect(707, 146, 64, 49);
    bloqueNuevo26->setBrush(Qt::transparent);
    bloqueNuevo26->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo26);

    QGraphicsRectItem *bloqueNuevo27 = scene->addRect(595, 152, 36, 50);
    bloqueNuevo27->setBrush(Qt::transparent);
    bloqueNuevo27->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo27);

    QGraphicsRectItem *bloqueNuevo28 = scene->addRect(578, 178, 17, 27);
    bloqueNuevo28->setBrush(Qt::transparent);
    bloqueNuevo28->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo28);

    QGraphicsRectItem *bloqueNuevo29 = scene->addRect(429, 128, 17, 27);
    bloqueNuevo29->setBrush(Qt::transparent);
    bloqueNuevo29->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo29);

    QGraphicsRectItem *bloqueNuevo30 = scene->addRect(787, 220, 17, 27);
    bloqueNuevo30->setBrush(Qt::transparent);
    bloqueNuevo30->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo30);

    QGraphicsRectItem *bloqueNuevo31 = scene->addRect(801, 335, 122, 1);
    bloqueNuevo31->setBrush(Qt::transparent);
    bloqueNuevo31->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo31);

    QGraphicsRectItem *bloqueNuevo32 = scene->addRect(804, 335, 1, 164);
    bloqueNuevo32->setBrush(Qt::transparent);
    bloqueNuevo32->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo32);

    QGraphicsRectItem *bloqueNuevo33 = scene->addRect(818, 497, 40, 82);
    bloqueNuevo33->setBrush(Qt::transparent);
    bloqueNuevo33->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo33);

    QGraphicsRectItem *bloqueNuevo34 = scene->addRect(806, 454, 25, 51);
    bloqueNuevo34->setBrush(Qt::transparent);
    bloqueNuevo34->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo34);

    QGraphicsRectItem *bloqueNuevo35 = scene->addRect(802, 600, 1, 62);
    bloqueNuevo35->setBrush(Qt::transparent);
    bloqueNuevo35->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo35);

    QGraphicsRectItem *bloqueNuevo36 = scene->addRect(874, 657, 27, 62);
    bloqueNuevo36->setBrush(Qt::transparent);
    bloqueNuevo36->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo36);

    QGraphicsRectItem *bloqueNuevo37 = scene->addRect(922, 573, 1, 146);
    bloqueNuevo37->setBrush(Qt::transparent);
    bloqueNuevo37->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo37);

    QGraphicsRectItem *bloqueNuevo38 = scene->addRect(921, 482, 1, 42);
    bloqueNuevo38->setBrush(Qt::transparent);
    bloqueNuevo38->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo38);

    QGraphicsRectItem *bloqueNuevo39 = scene->addRect(937, 615, 9, 42);
    bloqueNuevo39->setBrush(Qt::transparent);
    bloqueNuevo39->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo39);

    QGraphicsRectItem *bloqueNuevo40 = scene->addRect(803, 652, 1, 80);
    bloqueNuevo40->setBrush(Qt::transparent);
    bloqueNuevo40->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo40);

    QGraphicsRectItem *bloqueNuevo41 = scene->addRect(583, 816, 179, 63);
    bloqueNuevo41->setBrush(Qt::transparent);
    bloqueNuevo41->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo41);

    QGraphicsRectItem *bloqueNuevo42 = scene->addRect(699, 859, 56, 55);
    bloqueNuevo42->setBrush(Qt::transparent);
    bloqueNuevo42->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo42);

    QGraphicsRectItem *bloqueNuevo43 = scene->addRect(385, 883, 253, 35);
    bloqueNuevo43->setBrush(Qt::transparent);
    bloqueNuevo43->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo43);

    QGraphicsRectItem *bloqueNuevo44 = scene->addRect(384, 886, 1, 63);
    bloqueNuevo44->setBrush(Qt::transparent);
    bloqueNuevo44->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo44);

    QGraphicsRectItem *bloqueNuevo45 = scene->addRect(313, 884, 1, 63);
    bloqueNuevo45->setBrush(Qt::transparent);
    bloqueNuevo45->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo45);

    QGraphicsRectItem *bloqueNuevo46 = scene->addRect(418, 815, 207, 1);
    bloqueNuevo46->setBrush(Qt::transparent);
    bloqueNuevo46->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo46);

    QGraphicsRectItem *bloqueNuevo47 = scene->addRect(362, 751, 49, 41);
    bloqueNuevo47->setBrush(Qt::transparent);
    bloqueNuevo47->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo47);

    QGraphicsRectItem *bloqueNuevo48 = scene->addRect(351, 565, 1, 180);
    bloqueNuevo48->setBrush(Qt::transparent);
    bloqueNuevo48->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo48);

    QGraphicsRectItem *bloqueNuevo49 = scene->addRect(284, 546, 1, 180);
    bloqueNuevo49->setBrush(Qt::transparent);
    bloqueNuevo49->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo49);

    QGraphicsRectItem *bloqueNuevo50 = scene->addRect(355, 562, 111, 31);
    bloqueNuevo50->setBrush(Qt::transparent);
    bloqueNuevo50->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo50);

    QGraphicsRectItem *bloqueNuevo51 = scene->addRect(168, 615, 22, 37);
    bloqueNuevo51->setBrush(Qt::transparent);
    bloqueNuevo51->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo51);

    QGraphicsRectItem *bloqueNuevo52 = scene->addRect(265, 433, 29, 48);
    bloqueNuevo52->setBrush(Qt::transparent);
    bloqueNuevo52->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo52);

    QGraphicsRectItem *bloqueNuevo53 = scene->addRect(475, 494, 1, 67);
    bloqueNuevo53->setBrush(Qt::transparent);
    bloqueNuevo53->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo53);

    QGraphicsRectItem *bloqueNuevo54 = scene->addRect(475, 498, 97, 41);
    bloqueNuevo54->setBrush(Qt::transparent);
    bloqueNuevo54->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo54);

    QGraphicsRectItem *bloqueNuevo55 = scene->addRect(557, 505, 18, 59);
    bloqueNuevo55->setBrush(Qt::transparent);
    bloqueNuevo55->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo55);

    QGraphicsRectItem *bloqueNuevo56 = scene->addRect(638, 496, 1, 65);
    bloqueNuevo56->setBrush(Qt::transparent);
    bloqueNuevo56->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo56);

    QGraphicsRectItem *bloqueNuevo57 = scene->addRect(638, 496, 91, 40);
    bloqueNuevo57->setBrush(Qt::transparent);
    bloqueNuevo57->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo57);

    QGraphicsRectItem *bloqueNuevo58 = scene->addRect(703, 539, 14, 23);
    bloqueNuevo58->setBrush(Qt::transparent);
    bloqueNuevo58->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo58);

    QGraphicsRectItem *bloqueNuevo59 = scene->addRect(730, 334, 1, 162);
    bloqueNuevo59->setBrush(Qt::transparent);
    bloqueNuevo59->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo59);

    QGraphicsRectItem *bloqueNuevo60 = scene->addRect(512, 334, 219, 1);
    bloqueNuevo60->setBrush(Qt::transparent);
    bloqueNuevo60->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo60);

    QGraphicsRectItem *bloqueNuevo61 = scene->addRect(329, 369, 52, 34);
    bloqueNuevo61->setBrush(Qt::transparent);
    bloqueNuevo61->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo61);

    QGraphicsRectItem *bloqueNuevo62 = scene->addRect(453, 369, 52, 34);
    bloqueNuevo62->setBrush(Qt::transparent);
    bloqueNuevo62->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo62);

    QGraphicsRectItem *bloqueNuevo63 = scene->addRect(450, 370, 1, 65);
    bloqueNuevo63->setBrush(Qt::transparent);
    bloqueNuevo63->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo63);

    QGraphicsRectItem *bloqueNuevo64 = scene->addRect(382, 370, 1, 65);
    bloqueNuevo64->setBrush(Qt::transparent);
    bloqueNuevo64->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo64);

    QGraphicsRectItem *bloqueNuevo65 = scene->addRect(324, 251, 31, 34);
    bloqueNuevo65->setBrush(Qt::transparent);
    bloqueNuevo65->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo65);

    QGraphicsRectItem *bloqueNuevo66 = scene->addRect(409, 265, 14, 40);
    bloqueNuevo66->setBrush(Qt::transparent);
    bloqueNuevo66->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo66);

    QGraphicsRectItem *bloqueNuevo67 = scene->addRect(507, 275, 1, 88);
    bloqueNuevo67->setBrush(Qt::transparent);
    bloqueNuevo67->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo67);

    QGraphicsRectItem *bloqueNuevo68 = scene->addRect(425, 270, 80, 1);
    bloqueNuevo68->setBrush(Qt::transparent);
    bloqueNuevo68->setPen(Qt::NoPen);
    bloqueadores.append(bloqueNuevo68);


    currentDirection = None;
    moveTimer->stop();
    playerSpeed = 8;


    qDebug(" Nuevo mundo cargado.");

    dialogoSegundoMapa.clear();
    dialogoSegundoMapa
        << "Caballero: ESPERA... Como hiciste eso? donde estamos? como lograste hacer eso? "
        << "Brujo: Tranquilo, no olvides que soy mago y puedo hacer magia. "
        << "Brujo:  Y esta es una tierra sagrada y yo soy el protector de esta tierra. "
        << "Brujo: Pero al perder el Éterium, esta tierra sagrada quedó dañada."
        << "Caballero: Eso estoy viendo... Veo que el Éterium sí es importante."
        << "Brujo: Sí lo es. Porque el Éterium mantiene la paz de todo, y todos corremos peligro."
        << "Caballero: Y dime... ¿qué puedo hacer? No quiero que mi hogar quede destruido."
        << "Brujo: Deberás pasar por muchos desafíos, y en el camino harás amigos que te ayudarán."
        << "Brujo: Debes unir todos los fragmentos del eterium para asi poder restaurar la paz"
        << "Caballero:  Pero yo no puedo solo."
        << "Brujo: Que no se olvide que ya te habia dicho que mis amigas te van ayudar"
        << "Caballero: ahhhhhh..Ok, es cierto se me habia olvidado, ahora dime... ¿qué puedo hacer?"
        << "Brujo: Primero debes ayudar a Steve Latin. Los ogros del jefe secuestraron a su hermano,"
        << "Brujo: El se encuentra cerca de esta tierra debes encontrar y debes ayudarlo."
        << "Caballero: Que paso con su hermano?"
        << "Brujo: Creo que el hermano de steve latin logro robarle un fragmento del eterium pero los ogros,"
        << "Brujo: lo tienen capturado."
        << "Caballero: Ok, ayudaré a Steve Latin a recuperar a su hermano.";

    fraseActualSegundoMapa = 0;
    dialogoActivo = true;

    int margenLateral = 400;
    int margenInferior = 1000;
    int altoCaja = 140;

    dialogoCaja = scene->addRect(
        margenLateral,
        scene->height() - margenInferior,
        scene->width() - 2 * margenLateral,
        altoCaja,
        QPen(Qt::NoPen),
        QBrush(QColor(40, 60, 40, 220))
        );

    dialogoTexto = scene->addText("");
    dialogoTexto->setDefaultTextColor(Qt::white);
    dialogoTexto->setFont(QFont("Arial", 12, QFont::Normal));
    dialogoTexto->setTextWidth(dialogoCaja->rect().width() - 30);
    dialogoTexto->setPos(
        margenLateral + 15,
        scene->height() - margenInferior + 10
        );

    dialogoAyuda = scene->addText("[Espacio] → Siguiente");
    dialogoAyuda->setDefaultTextColor(Qt::yellow);
    dialogoAyuda->setFont(QFont("Arial", 13, QFont::Normal));
    dialogoAyuda->setPos(
        margenLateral + (scene->width() - 2 * margenLateral) - 260,
        scene->height() - margenInferior + altoCaja - 190
        );


    textoParcialSegundoMapa.clear();
    letraActualSegundoMapa = 0;

    if (timerTextoSegundoMapa == nullptr)
    {
        timerTextoSegundoMapa = new QTimer(this);
        connect(timerTextoSegundoMapa, &QTimer::timeout, this, &GameWindow::updateLetraSegundoMapa);
    }

    timerTextoSegundoMapa->start(40);

}
void GameWindow::updateAxemanIdle()
{
    if (!axeman) return;

    int frameWidth = 100;
    int frameHeight = 100;
    int idleFrames = 6;  // Ajusta si tu sprite tiene más o menos frames

    axeman->setPixmap(axemanIdleSheet.copy(axemanIdleFrameIndex * frameWidth, 0, frameWidth, frameHeight));

    axemanIdleFrameIndex = (axemanIdleFrameIndex + 1) % idleFrames;
}


void GameWindow::updateLetraSegundoMapa()
{
    if (fraseActualSegundoMapa >= dialogoSegundoMapa.size())
    {
        timerTextoSegundoMapa->stop();
        return;
    }

    QString fraseCompleta = dialogoSegundoMapa[fraseActualSegundoMapa];

    if (letraActualSegundoMapa < fraseCompleta.length())
    {
        textoParcialSegundoMapa += fraseCompleta[letraActualSegundoMapa];
        dialogoTexto->setPlainText(textoParcialSegundoMapa);
        letraActualSegundoMapa++;
    }
    else
    {
        timerTextoSegundoMapa->stop();
    }
}



// ------------------------------------------------- botones para mover caballero ------------------------------------------------
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    // Si estamos en diálogo, SOLO procesar Espacio:
    if (dialogoActivo)
    {
        if (event->key() == Qt::Key_Space)
        {
            if (mundoCambiado)
            {
                if (timerTextoSegundoMapa && timerTextoSegundoMapa->isActive())
                {
                    timerTextoSegundoMapa->stop();
                    dialogoTexto->setPlainText(dialogoSegundoMapa[fraseActualSegundoMapa]);
                }
                else
                {
                    fraseActualSegundoMapa++;

                    if (fraseActualSegundoMapa < dialogoSegundoMapa.size())
                    {
                        letraActualSegundoMapa = 0;
                        textoParcialSegundoMapa.clear();
                        dialogoTexto->setPlainText("");

                        timerTextoSegundoMapa->start(40);
                    }
                    else
                    {
                        // Fin del diálogo del segundo mapa
                        scene->removeItem(dialogoCaja);
                        scene->removeItem(dialogoTexto);
                        scene->removeItem(dialogoAyuda);

                        delete dialogoCaja;
                        delete dialogoTexto;
                        delete dialogoAyuda;

                        dialogoCaja = nullptr;
                        dialogoTexto = nullptr;
                        dialogoAyuda = nullptr;

                        dialogoActivo = false;

                        qDebug("¡Diálogo del segundo mapa terminado!");
                        // El caballero podrá moverse normalmente
                    }
                }
            }
            else
            {
                if (timerTextoWizard && timerTextoWizard->isActive())
                {
                    timerTextoWizard->stop();
                    dialogoTexto->setPlainText(dialogoWizard[fraseActualWizard]);
                }
                else
                {
                    fraseActualWizard++;

                    if (fraseActualWizard < dialogoWizard.size())
                    {
                        letraActualWizard = 0;
                        textoParcialWizard.clear();

                        dialogoTexto->setPlainText("");

                        if (timerTextoWizard == nullptr)
                        {
                            timerTextoWizard = new QTimer(this);
                            connect(timerTextoWizard, &QTimer::timeout, this, &GameWindow::updateLetraWizard);
                        }

                        timerTextoWizard->start(40);
                    }
                    else
                    {
                        // Fin del diálogo del PRIMER mapa
                        scene->removeItem(dialogoCaja);
                        scene->removeItem(dialogoTexto);
                        scene->removeItem(dialogoAyuda);

                        delete dialogoCaja;
                        delete dialogoTexto;
                        delete dialogoAyuda;

                        dialogoCaja = nullptr;
                        dialogoTexto = nullptr;
                        dialogoAyuda = nullptr;

                        dialogoActivo = false;

                        // Preguntar si quiere ir al otro mundo
                        QMessageBox::StandardButton reply;
                        reply = QMessageBox::question(this, "Mago", "¿Deseas ir a otro mundo?",
                                                      QMessageBox::Yes | QMessageBox::No);

                        if (reply == QMessageBox::Yes)
                        {
                            qDebug("Cambiando a nuevo mundo...");
                            cambiarAMundoNuevo();
                            mundoCambiado = true;
                        }
                        else
                        {
                            qDebug("Te quedas en este mundo.");

                            // Reactivar slimeTimer (Caballero se reactivará cuando toque teclas)
                            if (slimeTimer && !slimeTimer->isActive()) {
                                slimeTimer->start(150);
                            }
                        }
                    }
                }
            }
        }

        return;  // IMPORTANTE: No procesar otras teclas mientras hay diálogo
    }

    if (!player) return;

    if (event->isAutoRepeat()) return;

    // Si pasamos a movimiento → detener Idle animado
    if (idleTimer->isActive()) {
        idleTimer->stop();
        idleFrameIndex = 0;
    }

    switch (event->key()) {
    case Qt::Key_Up:
        currentDirection = Up;
        if (!moveTimer->isActive()) moveTimer->start(100);
        break;
    case Qt::Key_Down:
        currentDirection = Down;
        if (!moveTimer->isActive()) moveTimer->start(100);
        break;
    case Qt::Key_Left:
        currentDirection = Left;
        if (!moveTimer->isActive()) moveTimer->start(100);
        break;
    case Qt::Key_Right:
        currentDirection = Right;
        if (!moveTimer->isActive()) moveTimer->start(100);
        break;
    default:
        QDialog::keyPressEvent(event);
    }
}





void GameWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) return;

    switch (event->key()) {
    case Qt::Key_Up:
    case Qt::Key_Down:
    case Qt::Key_Left:
    case Qt::Key_Right:
        currentDirection = None;
        moveTimer->stop();

        // Iniciar Idle animado
        if (!idleSheet.isNull()) {
            idleFrameIndex = 0;
            idleTimer->start(250);
        }
        break;
    default:
        QDialog::keyReleaseEvent(event);
    }
}

void GameWindow::updateMovement()
{
    if (!player || currentDirection == None) return;

    int step = playerSpeed;

    int frameWidth = 100;
    int frameHeight = 100;
    int walkFrames = 8;

    qreal dx = 0, dy = 0;

    switch (currentDirection) {
    case Up:
        dy = -step;
        break;
    case Down:
        dy = step;
        break;
    case Left:
        dx = -step;
        break;
    case Right:
        dx = step;
        break;
    default:
        return;
    }

    // Verificar colisión
    if (!colisionaConBloqueadores(player, dx, dy)) {
        player->moveBy(dx, dy);
        checkWizardInteraction();


        checkSlimeInteraction();
        view->centerOn(player);

    } else {
        qDebug("Colisión detectada!");
    }

    // Animación Walk
    frameIndex = (frameIndex + 1) % walkFrames;
    player->setPixmap(walkSheet.copy(frameIndex * frameWidth, 0, frameWidth, frameHeight));

    // Mostrar/ocultar label del Mago
    if (labelMago && wizard)
    {
        qreal distanceMago = QLineF(player->scenePos(), wizard->scenePos()).length();
        if (distanceMago < 50.0) {
            labelMago->setVisible(true);
            labelMago->setPos(wizard->x() + 20, wizard->y() - 20);
        } else {
            labelMago->setVisible(false);
        }
    }

    // Mostrar/ocultar label del Slime
    if (labelSlime && slime)
    {
        qreal distanceSlime = QLineF(player->scenePos(), slime->scenePos()).length();
        if (distanceSlime < 50.0) {
            labelSlime->setVisible(true);
            labelSlime->setPos(slime->x() + 20, slime->y() - 20);
        } else {
            labelSlime->setVisible(false);
        }
    }
}


void GameWindow::updateIdle()
{
    if (!player) return;

    int frameWidth = 100;
    int frameHeight = 100;
    int idleFrames = 4;

    player->setPixmap(idleSheet.copy(idleFrameIndex * frameWidth, 0, frameWidth, frameHeight));

    idleFrameIndex = (idleFrameIndex + 1) % idleFrames;
}

void GameWindow::updateSlime()
{
    if (!slime) return;

    // Intentar mover en X
    if (!colisionaConBloqueadores(slime, slimeDx, 0)) {
        slime->moveBy(slimeDx, 0);
    } else {
        // Si colisiona → cambiar dirección X
        slimeDx = -slimeDx;
    }

    // Intentar mover en Y
    if (!colisionaConBloqueadores(slime, 0, slimeDy)) {
        slime->moveBy(0, slimeDy);
    } else {
        // Si colisiona → cambiar dirección Y
        slimeDy = -slimeDy;
    }

    // Animación Slime
    int frameWidth = 100;
    int frameHeight = 100;
    int walkFrames = 6;

    slime->setPixmap(slimeWalkSheet.copy(slimeFrameIndex * frameWidth, 0, frameWidth, frameHeight));

    slimeFrameIndex = (slimeFrameIndex + 1) % walkFrames;
}


//------------------------------------------------colisiones villa c++ --------------------------------------------
bool GameWindow::colisionaConBloqueadores(QGraphicsItem *item, qreal dx, qreal dy)
{
    if (!item) return false;

    // Simular movimiento
    item->moveBy(dx, dy);
    QList<QGraphicsItem*> colisiones = item->collidingItems();
    item->moveBy(-dx, -dy);

    for (QGraphicsItem *colItem : colisiones) {

        if (bloqueadores.contains(colItem)) {
            return true;
        }
    }
    return false;
}




