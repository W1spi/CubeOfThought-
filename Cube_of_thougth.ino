// Расширенный код с дополнительными пасхалками
#include <U8g2lib.h>
#include <Wire.h>
#include "esp_sleep.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

const int btnNext = 19;
const int btnPrev = 18;

const int maxCharsPerLine = 36;
const int linesPerPage = 4;
const int scrollDelay = 2000;
const int phraseDuration = 30000;

const char* phrases[] = {
  "Сломался? Значит, пора собрать себя иначе - прочнее.",
  "Было тяжело? Поздравляю, ты не сбежал.",
  "Упал? Отлично. Поднимайся. Земля - не твой дом.",
  "Руки опустились? Значит, пора ими оттолкнуться.",
  "Больно? Значит, ты жив. А значит - ещё можешь.",
  "Никто не понял? Это не твоя вина. Просто ты на шаг впереди.",
  "Сказали, не выйдет? Не забудь вернуться с результатом.",
  "Стало темно? Прекрасно видно, кто ты на самом деле.",
  "Ошибся? Значит, ты действовал. А не просто мечтал.",
  "Ничего не чувствуешь? Значит, пора вспомнить, зачем начал.",
  "Боишься? Значит, ты стоишь на границе роста.",
  "Хочешь сдаться? Отлично. Это значит - ты почти у цели.",
  "Не верят в тебя? Отличный повод сделать громче.",
  "Кажется, всё потеряно? Тогда терять нечего. Иди вперёд.",
  "Ты не сломанный. Ты перепрошиваешь себя под новый уровень.",
  "Если не ты - то кто? Если не сейчас - то когда?",
  "Ты не медленный. Ты просто идёшь по незнакомой дороге.",
  "Пауза - это не конец. Это затяжка перед прыжком.",
  "Ты не слаб. Ты просто человек. И это делает тебя сильнее.",
  "Всё рушится? Значит, ты близко к истине.",
  "Устал? Отдохни. Но не бросай.",
  "Ты - не результат ошибок. Ты - результат попыток.",
  "Не понимаешь, зачем? Продолжай. Ответ догонит позже.",
  "Ты не обязан быть железным. Главное - не ржаветь внутри.",
  "Слишком много чувств? Значит, ты жив. Значит, ты настоящий.",
  "Хочешь другого будущего? Перепиши код своей реальности.",
  "Тишина вокруг? Лучше услышишь себя.",
  "Думаешь, ты не тот? Проверь. А вдруг - именно ты.",
  "Идёшь один? Значит, ты первый.",
  "Уверенность не придёт сама. Она рождается из действия.",
  
    // 🎭 Играющие / провокационные
  "Время вышло? Тогда начни заново - на своих правилах.",
  "Не вписался? Создай свой контур.",
  "Ошибся? Стало быть, ты действовал, а не смотрел.",
  "Устал? Выдохни. И шагни дальше.",
  "Не видно выхода? Тогда ты внутри начала.",
  "Слишком сложно? Это уровень, где рождается сила.",
  "Не нравится путь? Протопчи новый.",
  "Сомневаешься? Это разум дышит.",
  "Падаешь? Земля ближе, чем казалась.",
  "Слишком тихо? Прислушайся к себе.",
  "Боишься? Ты жив. И ты идёшь.",
  "Перепутал шаги? Тогда танцуй.",
  "Заблудился? Так и находят себя.",
  "Все против? Значит, ты в точке перемен.",
  "Затерял смысл? Идеальное время придумать новый.",
  "Разрушен? Значит, ты свободен строить как хочешь.",
  "Не понимаю, что делаю? Значит, ищу по-настоящему.",
  "Всё рушится? Отлично. Значит, пора создать заново.",
  "Слишком много боли? Тогда ты всё ещё не сдался.",
  "Хаос внутри? Идеальное место для искры.",
  "Слишком тёмно? Ты и есть свет.",
  "Двигаюсь без цели? Иногда путь важнее конечной точки.",
  "Задержка - это не остановка.",
  "Тишина - это сцена перед первой репликой.",
  "Ты не сломался. Ты трансформируешься.",

  // 🌀 Философские
  "Чем глубже ночь - тем ярче звёзды внутри.",
  "Ты не конец истории. Ты её автор.",
  "Боль - это учитель, если ты не сбежал с урока.",
  "Настоящее - это точка, где прошлое и будущее спорят.",
  "Каждый миг - вопрос. Ответ - ты сам.",
  "Ничто не длится вечно. Ни хаос, ни страх.",
  "Ты не один. Ты часть огромного течения.",
  "Жизнь не объясняется - она ощущается.",
  "Даже стоя на месте, ты движешься внутри.",
  "Путь важнее победы. Победа - лишь точка запятой.",
  "Даже звёзды лучше свотрятся во тьме.",
  "Игра не имеет смысла, если ты не стремишься к победе.",
  "Человек, совершивший ошибку и не исправивший её, совершил ещё одну ошибку.",
  "Если свет свечи - это огонь, значит, пища была приготовлена очень давно.",
  "Если головоломка не сложилась, и тебе уже не собрать пазлы - начни сначала.",
  "Мы дойдём до самого конца! А потом ещё куда-нибудь...",
  "Страх - ещё один повод идти вперёд.",
  "Твоя история пишется прямо сейчас.",
  "Ты - наблюдатель и творец.",
  "Ничто не придаёт уверенности больше, чем опыт.",
  "Единственное, что можно сделать, это подойти к вопросу философски, то есть сказать себе: „Чёрт с ним“",
  "Лучше без точно сформулированной цели двигаться вперёд, чем без цели стоять на месте, и уж наверняка гораздо лучше, чем без цели пятиться назад.",

  // 🌤 Тёплые / поддерживающие
  "Ты делаешь лучше, чем думаешь.",
  "Твоё «ещё чуть-чуть» уже вдохновляет.",
  "Ты не обязан быть сильным каждый день.",
  "Даже в молчании ты ценен.",
  "Просто будь. Этого достаточно.",
  "Ты - причина чьей-то улыбки. Уже.",
  "Каждый шаг важен. Даже самый маленький.",
  "Ты не забыт. Мир знает о тебе.",
  "Просто дыши. Ты уже справляешься.",
  "Ты достоин. И точка."
};
const int phraseCount = sizeof(phrases) / sizeof(phrases[0]);

String lines[20];
int totalLines = 0;
int currentLine = 0;

int history[100];
int historyPos = 0;
int historyCount = 0;

unsigned long lastScrollTime = 0;
unsigned long startTime = 0;

unsigned long dualButtonStartTime = 0;
bool inEasterEgg = false;

bool prevBtnNext = false;
bool prevBtnPrev = false;

// Дополнительные переменные для новых пасхалок
unsigned long btnNextPressedTime = 0;
unsigned long btnPrevPressedTime = 0;

int konamiIndex = 0;
const int konamiLength = 4;
char konamiSeq[] = {'L', 'R', 'L', 'R'};

const char* easterEggText1 = "Самое главное - вглядеться пристально в тот мир, который тебя окружает: удивительнейшие тайны скрываются там, где их меньше всего ждёшь";
const char* easterEggText2 = "Мир любит тех, кто задаёт лишние вопросы. Потому что ответы хранятся за пределами инструкции.";
const char* easterEggText3 = "Иногда ответ не на поверхности. А глубже. Ты нашёл его. А значит, сможешь найти любой.";
const char* easterEggText4 = "Ты нашёл фразу, которой здесь быть не должно. Это уже делает тебя исследователем.";

void setup() {
  pinMode(btnNext, INPUT);
  pinMode(btnPrev, INPUT);

  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.setFont(u8g2_font_6x13_t_cyrillic);

  randomSeed(analogRead(0));
  int rnd = random(phraseCount);
  history[0] = rnd;
  historyCount = 1;
  drawPhrase(rnd);
  startTime = millis();
}

void loop() {
  unsigned long now = millis();

  bool btnN = digitalRead(btnNext);
  bool btnP = digitalRead(btnPrev);

  // Проверка на одновременное нажатие для основной пасхалки
  if (btnN && btnP) {
    if (dualButtonStartTime == 0) {
      dualButtonStartTime = now;
    } else if (!inEasterEgg && now - dualButtonStartTime >= 3000) {
      showEasterEgg(easterEggText1);
      return;
    }
  } else {
    dualButtonStartTime = 0;
  }

  // Проверка на долгое нажатие отдельно
  if (btnN) {
    if (btnNextPressedTime == 0) btnNextPressedTime = now;
    if (!inEasterEgg && now - btnNextPressedTime > 5000) {
      showEasterEgg(easterEggText3);
      return;
    }
  } else {
    btnNextPressedTime = 0;
  }

  if (btnP) {
    if (btnPrevPressedTime == 0) btnPrevPressedTime = now;
    if (!inEasterEgg && now - btnPrevPressedTime > 5000) {
      showEasterEgg(easterEggText4);
      return;
    }
  } else {
    btnPrevPressedTime = 0;
  }

  // Конями-пасхалка (влево, вправо, влево, вправо)
  if (btnN && !prevBtnNext) {
    if (konamiSeq[konamiIndex] == 'R') {
      konamiIndex++;
      if (konamiIndex >= konamiLength) {
        showEasterEgg(easterEggText2);
        konamiIndex = 0;
        return;
      }
    } else konamiIndex = 0;
  }
  if (btnP && !prevBtnPrev) {
    if (konamiSeq[konamiIndex] == 'L') {
      konamiIndex++;
      if (konamiIndex >= konamiLength) {
        showEasterEgg(easterEggText2);
        konamiIndex = 0;
        return;
      }
    } else konamiIndex = 0;
  }

  if (inEasterEgg) {
    if (btnN || btnP || now - startTime > 60000) {
      inEasterEgg = false;
      nextPhrase();
    }
    return;
  }

  if (now - lastScrollTime > scrollDelay) {
    currentLine++;
    if (currentLine > totalLines - linesPerPage) currentLine = 0;
    drawText();
    lastScrollTime = now;
  }

  if (now - startTime > phraseDuration) {
    nextPhrase();
  }

  if (btnN && !prevBtnNext) {
    nextPhrase();
  }
  prevBtnNext = btnN;

  if (btnP && !prevBtnPrev) {
    if (historyPos > 0) {
      historyPos--;
      drawPhrase(history[historyPos]);
    }
  }
  prevBtnPrev = btnP;

  esp_sleep_enable_timer_wakeup(50 * 1000);
  esp_light_sleep_start();
}

void nextPhrase() {
  int rnd;
  do {
    rnd = random(phraseCount);
  } while (historyCount > 0 && rnd == history[historyPos]);

  history[++historyPos] = rnd;
  historyCount = max(historyCount, historyPos + 1);
  drawPhrase(rnd);
  startTime = millis();
}

void drawPhrase(int index) {
  String text = String(phrases[index]);
  totalLines = 0;
  currentLine = 0;

  while (text.length() > 0) {
    String line = text.substring(0, maxCharsPerLine);
    lines[totalLines++] = line;
    text = text.substring(maxCharsPerLine);
  }
  lines[totalLines++] = "----------------------------------------";
  drawText();
}

void drawText() {
  u8g2.clearBuffer();
  for (int i = 0; i < linesPerPage; i++) {
    int lineIndex = currentLine + i;
    if (lineIndex >= totalLines) break;
    u8g2.setCursor(0, 15 + i * 16);
    u8g2.print(lines[lineIndex]);
  }
  u8g2.sendBuffer();
}

void showEasterEgg(const char* text) {
  inEasterEgg = true;
  startTime = millis();
  totalLines = 0;
  currentLine = 0;

  String t = String(text);
  while (t.length() > 0) {
    String line = t.substring(0, maxCharsPerLine);
    lines[totalLines++] = line;
    t = t.substring(maxCharsPerLine);
  }
  lines[totalLines++] = "----------------------------------------";
  drawText();
}
