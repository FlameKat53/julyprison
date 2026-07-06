/*
 * Toggle Switches — a minimal Qt6 widget app with four switches that do nothing.
 * Built for CachyOS (Arch Linux).  Requires: qt6-base cmake
 *
 *   mkdir build && cd build
 *   cmake ..
 *   cmake --build .
 *   ./ToggleSwitches
 */

#include <QApplication>
#include <QFont>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPalette>
#include <QWidget>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>

/* ------------------------------------------------------------------ */
/*  Hand-painted toggle switch                                        */
/* ------------------------------------------------------------------ */

class ToggleSwitch : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY toggled)

private:
    bool   m_checked   = false;
    QColor m_accent;
    QColor m_bg;

public:
    explicit ToggleSwitch(const QColor &accent, const QColor &bg, QWidget *parent = nullptr)
        : QWidget(parent), m_accent(accent), m_bg(bg)
    {
        setFixedSize(56, 30);
        setCursor(Qt::PointingHandCursor);
    }

    bool isChecked() const { return m_checked; }

    void setChecked(bool on)
    {
        if (m_checked == on) return;
        m_checked = on;
        update();
        emit toggled(on);
    }

signals:
    void toggled(bool);

protected:
    /* ---- click handler ---- */
    void mousePressEvent(QMouseEvent *ev) override
    {
        if (ev->button() == Qt::LeftButton) {
            setChecked(!m_checked);
        }
    }

    /* ---- paint the pill + knob ---- */
    void paintEvent(QPaintEvent *) override
    {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        QRectF r = rect().adjusted(2, 2, -2, -2);
        qreal radius = r.height() / 2.0;

        /* Pill track */
        QPainterPath pillPath;
        pillPath.addRoundedRect(r, radius, radius);

        p.setPen(Qt::NoPen);
        p.setBrush(m_checked ? m_accent : m_bg.lighter(140));
        p.drawPath(pillPath);

        /* Thin accent outline */
        p.setPen(m_accent);
        p.setBrush(Qt::NoBrush);
        p.drawPath(pillPath);

        /* Knob */
        qreal knobR   = r.height() / 2.0 - 4.0;
        qreal knobX   = m_checked ? r.right() - knobR - 4.0
                                  : r.left() + knobR + 4.0;
        qreal knobY   = r.center().y();

        /* Shadow */
        p.setBrush(QColor(0, 0, 0, 60));
        p.setPen(Qt::NoPen);
        p.drawEllipse(QPointF(knobX + 1, knobY + 2), knobR, knobR);

        /* Knob body */
        p.setBrush(Qt::white);
        p.drawEllipse(QPointF(knobX, knobY), knobR, knobR);
    }
};

/* ------------------------------------------------------------------ */
/*  Row: label + toggle                                               */
/* ------------------------------------------------------------------ */

class SwitchRow : public QWidget
{
public:
    explicit SwitchRow(const QString &label, const QColor &accent, const QColor &bg,
                       QWidget *parent = nullptr)
        : QWidget(parent)
    {
        auto *layout = new QHBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(14);

        auto *lbl = new QLabel(label, this);
        QFont f = lbl->font();
        f.setPixelSize(15);
        lbl->setFont(f);
        lbl->setStyleSheet("color: white;");

        auto *sw = new ToggleSwitch(accent, bg, this);

        layout->addStretch();
        layout->addWidget(lbl);
        layout->addWidget(sw);
        layout->addStretch();
    }
};

/* ------------------------------------------------------------------ */
/*  Main window                                                       */
/* ------------------------------------------------------------------ */

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("Toggle Switches");
        setMinimumSize(340, 310);

        /* ---- dark palette ---- */
        QPalette pal;
        pal.setColor(QPalette::Window,       QColor(0x1e, 0x1e, 0x2e));

        pal.setColor(QPalette::WindowText,   Qt::white);
        setPalette(pal);

        /* ---- layout ---- */
        auto *layout = new QVBoxLayout(this);
        layout->setSpacing(14);
        layout->setContentsMargins(36, 36, 36, 36);

        /* Title */
        auto *title = new QLabel("Toggle Switches", this);
        QFont bold = title->font();
        bold.setPixelSize(22);
        bold.setBold(true);
        title->setFont(bold);
        title->setAlignment(Qt::AlignCenter);
        layout->addWidget(title);

        /* Subtitle */
        auto *sub = new QLabel("These switches do absolutely nothing.", this);
        QFont small = sub->font();
        small.setPixelSize(12);
        sub->setFont(small);
        sub->setAlignment(Qt::AlignCenter);
        sub->setStyleSheet("color: white;");
        layout->addWidget(sub);

        /* Four switches */
        QColor bg(0x1e, 0x1e, 0x2e);
        struct SwitchInfo { const char *name; const char *color; };
        SwitchInfo switches[] = {
            {"Switch 1", "#7aa2f7"},
            {"Switch 2", "#9ece6a"},
            {"Switch 3", "#f7768e"},
            {"Switch 4", "#e0af68"},
        };

        for (const auto &s : switches) {
            layout->addWidget(new SwitchRow(s.name, QColor(s.color), bg, this));
        }

        layout->addStretch();
    }
};

/* ------------------------------------------------------------------ */
/*  Entry point                                                       */
/* ------------------------------------------------------------------ */

#include "main.moc"

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("ToggleSwitches");
    QApplication app(argc, argv);

    /* Disable native styling for consistent cross-platform look */
    QApplication::setStyle("Fusion");

    MainWindow w;
    w.show();
    return app.exec();
}
