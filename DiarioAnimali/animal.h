#ifndef ANIMAL_H
#define ANIMAL_H

#include <QString>
#include <QDateTime>
#include <QList>

enum class EventType {
    Vaccinazione,
    Visita,
    Toelettatura,
    Alimentazione,
    Altro
};

inline QString eventTypeToString(EventType t) {
    switch(t) {
        case EventType::Vaccinazione: return "Vaccinazione";
        case EventType::Visita: return "Visita";
        case EventType::Toelettatura: return "Toelettatura";
        case EventType::Alimentazione: return "Alimentazione";
        default: return "Altro";
    }
}

inline EventType stringToEventType(const QString &s){
    if(s == "Vaccinazione") return EventType::Vaccinazione;
    if(s == "Visita") return EventType::Visita;
    if(s == "Toelettatura") return EventType::Toelettatura;
    if(s == "Alimentazione") return EventType::Alimentazione;
    return EventType::Altro;
}

struct Evento {
    EventType tipo;
    QDateTime dataOra;
    QString descrizione;
};

struct Animale {
    QString nome;
    QString specie;
    QString razza;
    QDate dataNascita;
    double peso;
    QList<Evento> eventi;
};

#endif // ANIMAL_H
