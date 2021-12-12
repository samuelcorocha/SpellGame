// ProjetoPratico.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <fstream>
#include <string>
#include <speechapi_cxx.h>
#include <locale.h>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <conio.h>
#include <cctype>

using namespace std;
using namespace Microsoft::CognitiveServices::Speech;
using namespace Microsoft::CognitiveServices::Speech::Audio;

auto config = SpeechConfig::FromSubscription("2fedba6aeea94e3c88c9b8b175421032", "southcentralus");
auto audioConfig = AudioConfig::FromDefaultMicrophoneInput();

string recognizeSpeech()
{
    
    config->SetSpeechRecognitionLanguage("pt-BR");
    config->EnableDictation();

    auto recognizer = SpeechRecognizer::FromConfig(config, audioConfig);
    
    cout << "> ";
    auto result = recognizer->RecognizeOnceAsync().get();
    cout << result->Text << endl;

    return result->Text;
}

void synthesizeSpeech(string text)
{
    // Note: if only language is set, the default voice of that language is chosen.
    config->SetSpeechSynthesisLanguage("pt-br"); // e.g. "de-DE"
    // The voice setting will overwrite language setting.
    // The voice setting will not overwrite the voice element in input SSML.
    config->SetSpeechSynthesisVoiceName("pt-BR-AntonioNeural");

    auto synthesizer = SpeechSynthesizer::FromConfig(config);

    cout << text << endl;
    auto result = synthesizer->SpeakTextAsync(text).get();

    if (result->Reason == ResultReason::Canceled)
    {
        auto cancellation = SpeechSynthesisCancellationDetails::FromResult(result);
        cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

        if (cancellation->Reason == CancellationReason::Error)
        {
            cout << "CANCELED: ErrorCode=" << (int)cancellation->ErrorCode << std::endl;
            cout << "CANCELED: ErrorDetails=[" << cancellation->ErrorDetails << "]" << std::endl;
            cout << "CANCELED: Did you update the subscription info?" << std::endl;
        }
    }
}

void synthesizeSpeechWoutTxt(string text)
{
    // Note: if only language is set, the default voice of that language is chosen.
    config->SetSpeechSynthesisLanguage("pt-br"); // e.g. "de-DE"
    // The voice setting will overwrite language setting.
    // The voice setting will not overwrite the voice element in input SSML.
    config->SetSpeechSynthesisVoiceName("pt-BR-AntonioNeural");

    auto synthesizer = SpeechSynthesizer::FromConfig(config);

    auto result = synthesizer->SpeakTextAsync(text).get();

    if (result->Reason == ResultReason::Canceled)
    {
        auto cancellation = SpeechSynthesisCancellationDetails::FromResult(result);
        cout << "CANCELED: Reason=" << (int)cancellation->Reason << std::endl;

        if (cancellation->Reason == CancellationReason::Error)
        {
            cout << "CANCELED: ErrorCode=" << (int)cancellation->ErrorCode << std::endl;
            cout << "CANCELED: ErrorDetails=[" << cancellation->ErrorDetails << "]" << std::endl;
            cout << "CANCELED: Did you update the subscription info?" << std::endl;
        }
    }
}

int nivelDificuldade() {

    string dificuldade;

    synthesizeSpeech("Selecione o nivel de dificuldade:\nFácil, normal ou difícil?");
    
    while (true)
    {
        dificuldade = recognizeSpeech();

        if (dificuldade == "Fácil.")
        {
            synthesizeSpeech("Ótimo! Nível fácil escolhido.\nBoa sorte!");
            return 1;
        }
        else if (dificuldade == "Normal.")
        {
            synthesizeSpeech("Ótimo! Nível normal escolhido.\nBoa sorte!");
            return 2;
        }
        else if (dificuldade == "Difícil.")
        {
            synthesizeSpeech("Ótimo! Nível difícil escolhido.\nBoa sorte!");
            return 3;
        }
        else
            synthesizeSpeech("Não entendi, pode repetir?");
    }
}

string buscaPalavra(int dificuldade)
{
    srand(time(0));

    int palavra = rand() % 10;

    switch (dificuldade)
    {
    case 1:
        switch (palavra) {

        case 0:
            return "Bola";
            break;

        case 1:
            return "Carro";
            break;

        case 2:
            return "Porta";
            break;

        case 3:
            return "Quadro";
            break;

        case 4:
            return "Chuva";
            break;

        case 5:
            return "Foto";
            break;

        case 6:
            return "Festa";
            break;

        case 7:
            return "Sandro";
            break;

        case 8:
            return "Praia";
            break;

        case 9:
            return "Nuvem";
            break;

        }
        break;

    case 2:
        switch (palavra) {

        case 0:
            return "Sorvete";
            break;

        case 1:
            return "Iogurte";
            break;

        case 2:
            return "Assassino";
            break;

        case 3:
            return "Geladeira";
            break;

        case 4:
            return "Computador";
            break;

        case 5:
            return "Cachoeira";
            break;

        case 6:
            return "Avestruz";
            break;

        case 7:
            return "Excelente";
            break;

        case 8:
            return "Ensolarado";
            break;

        case 9:
            return "Aeroporto";
            break;
        }
        break;

    case 3:
        switch (palavra) {

        case 0:
            return "Avia��o";
            break;

        case 1:
            return "N�made";
            break;

        case 2:
            return "Rodovi�ria";
            break;

        case 3:
            return "Helic�ptero";
            break;

        case 4:
            return "Inunda��o";
            break;

        case 5:
            return "Eg�pcios";
            break;

        case 6:
            return "Arist�teles";
            break;

        case 7:
            return "Hist�rico";
            break;

        case 8:
            return "R�ptil";
            break;

        case 9:
            return "Antropol�gico";
            break;
        }
        break;
    }
}

void soletrando(string nome, string palavra)
{
    synthesizeSpeech(nome + ", soletre a palavra");
    cout << "...";
    synthesizeSpeechWoutTxt(palavra);

    string palavraSoletrada = recognizeSpeech();

    if (palavra == palavraSoletrada)
    {
        synthesizeSpeech("Parabéns " + nome + " Está correto!");
    }
    else
    {
        synthesizeSpeech("Que pena, " + nome + " Está errado!");
    }
}

int main()
{
    setlocale(LC_ALL, ".UTF8");

    synthesizeSpeech("Bem vindo ao soletrando! Primeiramente, qual o seu nome?");
    string playerName = recognizeSpeech();

    system("CLS");

    synthesizeSpeech("Olá " + playerName);

    system("CLS");

    while (true) {
        int dificuldade = nivelDificuldade();

        system("CLS");
        while (true)
        {

            string palavra = buscaPalavra(dificuldade) + ".";
            for_each(palavra.begin(), palavra.end(), [](char& c) {
                c = ::toupper(c);
            });

            soletrando(playerName, palavra);

            system("CLS");

            synthesizeSpeech("Deseja continuar?");
            string continuar = recognizeSpeech();

            if (continuar == "Não.")
                break;
        }
        system("CLS");

        synthesizeSpeech("Deseja mudar de dificuldade?");
        string continuar = recognizeSpeech();

        if (continuar == "Não.")
            break;

        system("CLS");
    }

    synthesizeSpeech("Obrigado, " + playerName + " Foi muito bom jogar com você!");


    return 0;
}