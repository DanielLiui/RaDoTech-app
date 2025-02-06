#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QDateTime>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QMap>

//FIXME: For better compliance with C++ standard, this should probably be not in a header file

struct MeasurementRecord {
    QDateTime timestamp;
    QMap<QString, double> measurements;
    double overallScore;

    QJsonObject toJson() const {
        QJsonObject json;
        json["timestamp"] = timestamp.toString(Qt::ISODate);
        json["overallScore"] = overallScore;

        QJsonObject measurementsObj;
        for (auto it = measurements.begin(); it != measurements.end(); ++it) {
            measurementsObj[it.key()] = it.value();
        }
        json["measurements"] = measurementsObj;
        
        return json;
    }

    static MeasurementRecord fromJson(const QJsonObject& json) {
        MeasurementRecord record;
        record.timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
        record.overallScore = json["overallScore"].toDouble();
        
        QJsonObject measurementsObj = json["measurements"].toObject();
        for (auto it = measurementsObj.begin(); it != measurementsObj.end(); ++it) {
            record.measurements[it.key()] = it.value().toDouble();
        }
        
        return record;
    }
};

class UserData {
public:
    QString username;
    QString password;  // Changed from passwordHash to password
    QString fullName;
    int age;
    QString gender;
    int height;
    int weight;
    QString medicalConditions;
    QString medications;
    QVector<MeasurementRecord> measurementHistory;

    QJsonObject toJson() const {
        QJsonObject json;
        json["username"] = username;
        json["password"] = password;
        json["fullName"] = fullName;
        json["age"] = age;
        json["gender"] = gender;
        json["height"] = height;
        json["weight"] = weight;
        json["medicalConditions"] = medicalConditions;
        json["medications"] = medications;

        QJsonArray historyArray;
        for (const auto& record : measurementHistory) {
            historyArray.append(record.toJson());
        }
        json["measurementHistory"] = historyArray;

        return json;
    }

    static UserData fromJson(const QJsonObject& json) {
        UserData userData;
        userData.username = json["username"].toString();
        userData.password = json["password"].toString(); 
        userData.fullName = json["fullName"].toString();
        userData.age = json["age"].toInt();
        userData.gender = json["gender"].toString();
        userData.height = json["height"].toInt();
        userData.weight = json["weight"].toInt();
        userData.medicalConditions = json["medicalConditions"].toString();
        userData.medications = json["medications"].toString();

        QJsonArray historyArray = json["measurementHistory"].toArray();
        for (const auto& value : historyArray) {
            userData.measurementHistory.append(
                MeasurementRecord::fromJson(value.toObject())
            );
        }

        return userData;
    }

    void addMeasurement(const QMap<QString, double>& measurements) {
        MeasurementRecord record;
        record.timestamp = QDateTime::currentDateTime();
        record.measurements = measurements;
        
        double sum = 0.0;
        for (auto value : measurements.values()) {
            sum += value;
        }
        record.overallScore = measurements.isEmpty() ? 0.0 : sum / measurements.size();

        measurementHistory.append(record);
    }
};

#endif // USERDATA_H
