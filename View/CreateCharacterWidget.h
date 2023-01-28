#ifndef CREATE_CHARACTER_WIDGET_H
#define CREATE_CHARACTER_WIDGET_H

#include <QLineEdit>
#include <QSpinBox>
#include <QString>
#include <QComboBox>

class CreateCharacterWidget: public QFrame {
Q_OBJECT
private:
    QComboBox* type;
    QLineEdit* name;
    QSpinBox* max_hp;
    QSpinBox* power;
    QSpinBox* level_armor;

public:
    explicit CreateCharacterWidget(QWidget* parent = 0);
    bool isValid() const;

    QString getTypeText() const;
    QString getNameText() const;
    int getMaxHpValue() const;
    int getPowerValue() const;
    int getLevelArmorValue() const;

    QComboBox* getTypeWidget() const;
    QLineEdit* getNameWidget() const;
    QSpinBox* getMaxHpWidget() const;
    QSpinBox* getPowerWidget() const;
    QSpinBox* getLevelArmorWidget() const;

signals:
    void remove(CreateCharacterWidget*);

public slots:
    void removeCharacter();
};

#endif