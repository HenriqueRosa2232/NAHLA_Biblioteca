#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QDir>
#include <QDebug>
#include <QSqlQuery>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);


    QSqlDatabase banco = QSqlDatabase::addDatabase("QSQLITE");
    banco.setDatabaseName("nahla.db");
    qDebug() << "Banco localizado em:"
             << QFileInfo(banco.databaseName()).absoluteFilePath();

    if (banco.open()) {
        qDebug() << "Banco NAHLA aberto com sucesso!";

        QSqlQuery query;

        if (query.exec(
                "CREATE TABLE IF NOT EXISTS usuarios ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "matricula TEXT UNIQUE NOT NULL, "
                "nome TEXT NOT NULL, "
                "tipo TEXT NOT NULL)"
                )) {
            qDebug() << "Tabela usuarios criada ou ja existente!";
        } else {
            qDebug() << "Erro ao criar tabela:" << query.lastError().text();
        }

        QSqlQuery inserir;

        inserir.prepare(
            "INSERT OR IGNORE INTO usuarios (matricula, nome, tipo) "
            "VALUES (:matricula, :nome, :tipo)"
            );

        inserir.bindValue(":matricula", "202500123");
        inserir.bindValue(":nome", "Ana Silva");
        inserir.bindValue(":tipo", "Aluno");

        if (inserir.exec()) {
            qDebug() << "Usuario de teste inserido ou ja existente!";
        } else {
            qDebug() << "Erro ao inserir usuario:" << inserir.lastError().text();
        }


        QSqlQuery consulta;

        consulta.prepare(
            "SELECT matricula, nome, tipo FROM usuarios "
            "WHERE matricula = :matricula"
            );

        consulta.bindValue(":matricula", "202500123");

        if (consulta.exec() && consulta.next()) {
            qDebug() << "Usuario encontrado:";
            qDebug() << "Matricula:" << consulta.value("matricula").toString();
            qDebug() << "Nome:" << consulta.value("nome").toString();
            qDebug() << "Tipo:" << consulta.value("tipo").toString();
        } else {
            qDebug() << "Usuario nao encontrado ou ocorreu um erro:"
                     << consulta.lastError().text();
        }


    } else {
        qDebug() << "Erro ao abrir banco:" << banco.lastError().text();
    }



}

LoginWindow::~LoginWindow()
{
    delete ui;
}
