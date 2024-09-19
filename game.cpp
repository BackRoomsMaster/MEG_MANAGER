#include "game.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

Game::Game() : currentDay(1), entitiesContained(0), hasCenterOperativo(false) {
    player = Player("Scienziato MEG", 100, 10);
    initializeStructures();
    initializeBackroomsLevels();
    
    // Inizializza il generatore di numeri casuali
    srand(static_cast<unsigned int>(time(nullptr)));
}

void Game::play() {
    std::cout << "Benvenuto nel gioco di esplorazione delle Backrooms!\n";
    
    while (player.getHealth() > 0) {
        playDay();
        
        if (entitiesContained >= 10) {
            std::cout << "Congratulazioni! Hai contenuto 10 entità e hai vinto il gioco!\n";
            break;
        }
    }
    
    if (player.getHealth() <= 0) {
        std::cout << "Game Over! Il tuo personaggio è morto.\n";
    }
    
    std::cout << "Grazie per aver giocato!\n";
}

void Game::playDay() {
    std::cout << "\n--- Giorno " << currentDay << " ---\n";
    displayStatus();
    
    std::cout << "Cosa vuoi fare? (muovi/interagisci/riposa/costruisci";
    if (hasCenterOperativo) std::cout << "/gestisci-esploratori";
    std::cout << "): ";
    std::string action;
    std::cin >> action;

    if (action == "muovi") {
        movePlayer();
    } else if (action == "interagisci") {
        interactWithEntity();
    } else if (action == "riposa") {
        restPlayer();
    } else if (action == "costruisci") {
        buildStructure();
    } else if (action == "gestisci-esploratori" && hasCenterOperativo) {
        manageExplorers();
    } else {
        std::cout << "Azione non valida.\n";
    }

    currentDay++;
}

void Game::displayStatus() {
    std::cout << "Salute: " << player.getHealth() << "\n";
    std::cout << "Conoscenza: " << player.getKnowledge() << "\n";
    std::cout << "Livello: " << player.getLevel() << "\n";
    std::cout << "Esperienza: " << player.getExperience() << "/" << (100 * player.getLevel()) << "\n";
    std::cout << "Risorse:\n";
    std::cout << "  Metallo: " << player.getResource("metallo") << "\n";
    std::cout << "  Elettronica: " << player.getResource("elettronica") << "\n";
    std::cout << "  Energia: " << player.getResource("energia") << "\n";
    std::cout << "Entità contenute: " << entitiesContained << "\n";
}

void Game::movePlayer() {
    std::cout << "Ti muovi attraverso le Backrooms...\n";
    player.addResource("metallo", rand() % 5 + 1);
    player.addResource("elettronica", rand() % 3 + 1);
    player.addResource("energia", rand() % 4 + 1);
    
    if (rand() % 100 < 30) {
        entityQueue.push(getRandomEntity());
        std::cout << "Hai incontrato un " << entityQueue.back().getName() << "!\n";
    }
}

void Game::interactWithEntity() {
    if (entityQueue.empty()) {
        std::cout << "Non ci sono entità con cui interagire.\n";
        return;
    }
    
    Entity& entity = entityQueue.front();
    std::cout << "Stai interagendo con un " << entity.getName() << ".\n";
    std::cout << "Vuoi studiarlo o tentare di contenerlo? (studia/contieni): ";
    std::string action;
    std::cin >> action;
    
    if (action == "studia") {
        studyEntity(entity);
    } else if (action == "contieni") {
        containEntity(entity);
    } else {
        std::cout << "Azione non valida.\n";
    }
}

void Game::restPlayer() {
    std::cout << "Ti riposi e recuperi le forze.\n";
    player.takeDamage(-20);  // Guarisci di 20 punti salute
}

void Game::buildStructure() {
    std::cout << "Strutture disponibili:\n";
    for (size_t i = 0; i < availableStructures.size(); ++i) {
        std::cout << i + 1 << ". " << availableStructures[i].getName() << "\n";
        for (const auto& cost : availableStructures[i].getCost()) {
            std::cout << "   " << cost.first << ": " << cost.second << "\n";
        }
    }
    
    std::cout << "Quale struttura vuoi costruire? (0 per annullare): ";
    int choice;
    std::cin >> choice;
    
    if (choice == 0 || choice > static_cast<int>(availableStructures.size())) {
        return;
    }
    
    const Structure& selectedStructure = availableStructures[choice - 1];
    bool canBuild = true;
    
    for (const auto& cost : selectedStructure.getCost()) {
        if (player.getResource(cost.first) < cost.second) {
            canBuild = false;
            break;
        }
    }
    
    if (canBuild) {
        for (const auto& cost : selectedStructure.getCost()) {
            player.useResource(cost.first, cost.second);
        }
        builtStructures[selectedStructure.getName()]++;
        std::cout << "Hai costruito " << selectedStructure.getName() << "!\n";
        
        if (selectedStructure.getName() == "Centro operativo") {
            hasCenterOperativo = true;
            std::cout << "Ora puoi gestire una squadra di esploratori!\n";
        }
    } else {
        std::cout << "Non hai abbastanza risorse per costruire questa struttura.\n";
    }
}

void Game::manageExplorers() {
    while (true) {
        std::cout << "\n--- Gestione Esploratori ---\n";
        std::cout << "1. Visualizza esploratori\n";
        std::cout << "2. Visualizza dettagli esploratori\n";
        std::cout << "3. Assumi nuovo esploratore\n";
        std::cout << "4. Cura esploratori\n";
        std::cout << "5. Esplora un livello delle Backrooms\n";
        std::cout << "6. Torna al menu principale\n";
        std::cout << "Scelta: ";
        
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                displayExplorers();
                break;
            case 2:
                displayDetailedExplorers();
                break;
            case 3:
                hireExplorer();
                break;
            case 4:
                healExplorers();
                break;
            case 5:
                exploreBackroomsLevel();
                break;
            case 6:
                return;
            default:
                std::cout << "Scelta non valida.\n";
        }
    }
}

void Game::hireExplorer() {
    int explorerCapacity = 5;  // Capacità di base
    for (const auto& pair : builtStructures) {
        auto it = std::find_if(availableStructures.begin(), availableStructures.end(),
                               [&](const Structure& s) { return s.getName() == pair.first; });
        if (it != availableStructures.end()) {
            explorerCapacity += it->getExplorerCapacityBonus() * pair.second;
        }
    }

    if (explorers.size() >= explorerCapacity) {
        std::cout << "Hai raggiunto il limite massimo di esploratori (" << explorerCapacity << ").\n";
        return;
    }

    if (player.getResource("energia") >= 50) {
        std::string name = "Esploratore " + std::to_string(explorers.size() + 1);
        int health = 80 + rand() % 41;  // 80-120
        int sanity = 70 + rand() % 31;  // 70-100
        int skill = 5 + rand() % 6;     // 5-10
        explorers.emplace_back(name, health, sanity, skill);
        player.useResource("energia", 50);
        std::cout << "Hai assunto " << name << "!\n";
    } else {
        std::cout << "Non hai abbastanza energia per assumere un nuovo esploratore.\n";
    }
}

void Game::healExplorers() {
    int totalHealthRestore = 0;
    int totalSanityRestore = 0;
    for (const auto& pair : builtStructures) {
        auto it = std::find_if(availableStructures.begin(), availableStructures.end(),
                               [&](const Structure& s) { return s.getName() == pair.first; });
        if (it != availableStructures.end()) {
            totalHealthRestore += it->getHealthRestoreBonus() * pair.second;
            totalSanityRestore += it->getSanityRestoreBonus() * pair.second;
        }
    }

    for (auto& explorer : explorers) {
        explorer.heal(totalHealthRestore);
        explorer.restoreSanity(totalSanityRestore);
    }

    std::cout << "Gli esploratori sono stati curati e hanno recuperato sanità mentale.\n";
}

void Game::displayExplorers() const {
    std::cout << "\n--- Esploratori ---\n";
    for (size_t i = 0; i < explorers.size(); ++i) {
        const auto& explorer = explorers[i];
        std::cout << i + 1 << ". " << explorer.getName() << " (Livello: " << explorer.getLevel() << ")\n";
    }
}

void Game::displayDetailedExplorers() const {
    std::cout << "\n--- Dettagli Esploratori ---\n";
    for (size_t i = 0; i < explorers.size(); ++i) {
        const auto& explorer = explorers[i];
        std::cout << i + 1 << ". " << explorer.getName() << "\n";
        std::cout << "   Salute: " << explorer.getHealth() << "/" << explorer.getMaxHealth() << "\n";
        std::cout << "   Sanità: " << explorer.getSanity() << "/" << explorer.getMaxSanity() << "\n";
        std::cout << "   Abilità: " << explorer.getSkill() << "\n";
        std::cout << "   Livello: " << explorer.getLevel() << "\n";
        std::cout << "   Esperienza: " << explorer.getExperience() << "/" << (100 * explorer.getLevel()) << "\n\n";
    }
}

void Game::exploreBackroomsLevel() {
    if (explorers.empty()) {
        std::cout << "Non hai esploratori da inviare in missione.\n";
        return;
    }

    displayBackroomsLevels();
    std::cout << "Seleziona il livello da esplorare: ";
    int levelChoice;
    std::cin >> levelChoice;

    if (levelChoice < 1 || levelChoice > static_cast<int>(backroomsLevels.size())) {
        std::cout << "Scelta non valida.\n";
        return;
    }

    const Level& chosenLevel = backroomsLevels[levelChoice - 1];

    displayDetailedExplorers();
    std::cout << "Seleziona gli esploratori da inviare in missione (separati da spazi, 0 per terminare): ";
    std::vector<Explorer*> missionTeam;
    
    while (true) {
        int choice;
        std::cin >> choice;
        if (choice == 0) break;
        if (choice > 0 && choice <= static_cast<int>(explorers.size())) {
            missionTeam.push_back(&explorers[choice - 1]);
        }
    }

    if (missionTeam.empty()) {
        std::cout << "Nessun esploratore selezionato. La missione è annullata.\n";
        return;
    }

    std::cout << "La squadra è stata inviata per esplorare " << chosenLevel.getName() << ".\n";
    missionResult(chosenLevel, missionTeam);
}

void Game::missionResult(const Level& level, std::vector<Explorer*>& team) {
    int difficultyFactor;
    switch (level.getDifficulty()) {
        case Difficulty::Easy: difficultyFactor = 1; break;
        case Difficulty::Medium: difficultyFactor = 2; break;
        case Difficulty::Hard: difficultyFactor = 3; break;
        case Difficulty::Extreme: difficultyFactor = 5; break;
    }

    int teamSkill = 0;
    int totalStudyBonus = getTotalStudyBonus();
    int totalContainmentBonus = getTotalContainmentBonus();

    for (const auto& explorer : team) {
        teamSkill += explorer->getSkill();
    }

    int successChance = std::min(80, (teamSkill + totalStudyBonus + totalContainmentBonus) * 10 / (difficultyFactor * 5));
    
    if (rand() % 100 < successChance) {
        std::cout << "La missione è stata un successo!\n";
        for (auto& explorer : team) {
            int expGain = 20 * difficultyFactor;
            explorer->gainExperience(expGain);
            std::cout << explorer->getName() << " ha guadagnato " << expGain << " punti esperienza.\n";
            
            // Perdita di sanità mentale anche in caso di successo
            int sanityLoss = (rand() % 5 + 1) * difficultyFactor;
            explorer->takeSanityDamage(sanityLoss);
            std::cout << explorer->getName() << " ha perso " << sanityLoss << " punti sanità.\n";
            
            // Possibilità di catturare un'entità
            if (rand() % 100 < 30 + totalContainmentBonus) {
                const Entity& capturedEntity = level.getEntities()[rand() % level.getEntities().size()];
                activeEntities.push_back(capturedEntity);
                std::cout << "La squadra ha catturato un " << capturedEntity.getName() << "!\n";
            }
        }
    } else {
        std::cout << "La missione è fallita.\n";
        for (auto& explorer : team) {
            int damageTaken = (rand() % 30 + 20) * difficultyFactor;
            explorer->takeDamage(damageTaken);
            std::cout << explorer->getName() << " ha subito " << damageTaken << " danni.\n";
            
            int sanityLoss = (rand() % 10 + 5) * difficultyFactor;
            explorer->takeSanityDamage(sanityLoss);
            std::cout << explorer->getName() << " ha perso " << sanityLoss << " punti sanità.\n";
            
            if (!explorer->isAlive()) {
                std::cout << explorer->getName() << " è stato sconfitto.\n";
            } else if (!explorer->isSane()) {
                std::cout << explorer->getName() << " ha perso la ragione ed è stato rimosso dalla squadra.\n";
            } else {
                // La probabilità di dispersione aumenta con la diminuzione della sanità mentale
                int dispersionChance = 10 * difficultyFactor + (100 - explorer->getSanity());
                if (rand() % 100 < dispersionChance) {
                    std::cout << explorer->getName() << " si è disperso nelle Backrooms.\n";
                    explorer->takeDamage(explorer->getHealth());  // Rimuovi l'esploratore
                }
            }
        }
    }

    // Rimuovi gli esploratori morti, impazziti o dispersi
    explorers.erase(std::remove_if(explorers.begin(), explorers.end(),
                                   [](const Explorer& e) { return !e.isAlive() || !e.isSane(); }),
                    explorers.end());
}

void Game::studyEntity(Entity& entity) {
    int studyChance = player.getKnowledge() * 5 + getTotalStudyBonus();
    if (rand() % 100 < studyChance) {
        std::cout << "Hai studiato con successo l'entità!\n";
        player.increaseKnowledge(entity.getStudyDifficulty());
        player.gainExperience(entity.getExperienceValue());
        entityQueue.pop();
    } else {
        std::cout << "Non sei riuscito a studiare l'entità.\n";
        player.takeDamage(entity.getDamage());
    }
}

void Game::containEntity(Entity& entity) {
    int containChance = player.getKnowledge() * 3 + getTotalContainmentBonus();
    if (rand() % 100 < containChance) {
        std::cout << "Hai contenuto con successo l'entità!\n";
        player.gainExperience;
        player.gainExperience(entity.getExperienceValue() * 2);
        entitiesContained++;
        entityQueue.pop();
    } else {
        std::cout << "Non sei riuscito a contenere l'entità.\n";
        player.takeDamage(entity.getDamage() * 2);
    }
}

int Game::getTotalStudyBonus() const {
    int totalBonus = 0;
    for (const auto& pair : builtStructures) {
        auto it = std::find_if(availableStructures.begin(), availableStructures.end(),
                               [&](const Structure& s) { return s.getName() == pair.first; });
        if (it != availableStructures.end()) {
            totalBonus += it->getStudyBonus() * pair.second;
        }
    }
    return totalBonus;
}

int Game::getTotalContainmentBonus() const {
    int totalBonus = 0;
    for (const auto& pair : builtStructures) {
        auto it = std::find_if(availableStructures.begin(), availableStructures.end(),
                               [&](const Structure& s) { return s.getName() == pair.first; });
        if (it != availableStructures.end()) {
            totalBonus += it->getContainmentBonus() * pair.second;
        }
    }
    return totalBonus;
}

void Game::initializeStructures() {
    availableStructures = {
        Structure("Laboratorio di base", {{"metallo", 50}, {"elettronica", 30}}, 5, 0, 0, 0, 1),
        Structure("Camera di contenimento base", {{"metallo", 70}, {"energia", 40}}, 0, 5, 0, 0, 0),
        Structure("Centro di analisi", {{"elettronica", 60}, {"energia", 50}}, 3, 3, 0, 0, 2),
        Structure("Generatore di campo", {{"metallo", 40}, {"energia", 80}}, 2, 4, 0, 0, 0),
        Structure("Centro operativo", {{"metallo", 100}, {"elettronica", 100}, {"energia", 100}}, 0, 0, 0, 0, 5),
        Structure("Infermeria", {{"metallo", 80}, {"elettronica", 70}, {"energia", 60}}, 0, 0, 20, 10, 0),
        Structure("Centro di ricerca avanzato", {{"metallo", 150}, {"elettronica", 200}, {"energia", 180}}, 10, 5, 0, 0, 3),
        Structure("Struttura di contenimento avanzata", {{"metallo", 200}, {"elettronica", 150}, {"energia", 250}}, 5, 15, 0, 0, 0),
        Structure("Centro benessere", {{"metallo", 100}, {"elettronica", 80}, {"energia", 120}}, 0, 0, 10, 30, 0),
        Structure("Generatore di energia quantica", {{"metallo", 300}, {"elettronica", 350}, {"energia", 400}}, 5, 5, 0, 0, 5),
        Structure("Laboratorio di realtà virtuale", {{"metallo", 250}, {"elettronica", 400}, {"energia", 300}}, 15, 0, 0, 20, 2),
        Structure("Bunker di isolamento", {{"metallo", 500}, {"elettronica", 300}, {"energia", 450}}, 0, 25, 0, 15, 0)
    };
}

void Game::initializeBackroomsLevels() {
    backroomsLevels = {
        Level("Il Limbo", "Un vasto spazio di uffici vuoti e moquette gialla.", Difficulty::Easy, {Entity("Hound", 30, 10), Entity("Faceling", 40, 15)}),
        Level("La Fabbrica Abbandonata", "Un labirinto di macchinari arrugginiti e nastri trasportatori.", Difficulty::Easy, {Entity("Smiler", 50, 20), Entity("Dullers", 20, 5)}),
        Level("Il Corridoio Infinito", "Un corridoio che sembra non avere fine, con porte identiche su entrambi i lati.", Difficulty::Easy, {Entity("Clumps", 35, 12), Entity("Crawlers", 60, 18)}),
        Level("La Biblioteca Dimenticata", "Scaffali infiniti di libri illeggibili in una biblioteca senza fine.", Difficulty::Medium, {Entity("Skin-Stealer", 70, 25), Entity("Deathmoths", 40, 30)}),
        Level("Il Labirinto di Specchi", "Un intricato labirinto di specchi che distorcono la realtà.", Difficulty::Medium, {Entity("Wretch", 80, 28), Entity("Facerooms", 90, 20)}),
        Level("La Città Sommersa", "Una metropoli subacquea con edifici contorti e strade allagate.", Difficulty::Medium, {Entity("Bursters", 50, 35), Entity("Stalkers", 75, 26)}),
        Level("La Torre dell'Orologio", "Una torre che si estende all'infinito, piena di ingranaggi e meccanismi in movimento.", Difficulty::Hard, {Entity("Skin Lords", 110, 40), Entity("Clowns", 70, 30)}),
        Level("Il Vuoto Bianco", "Uno spazio infinito di bianco accecante, senza riferimenti o orizzonti.", Difficulty::Hard, {Entity("Smogs", 100, 25), Entity("Howlers", 85, 35)}),
        Level("La Soglia del Caos", "Un luogo dove la realtà si sfalda e le leggi della fisica non hanno più senso.", Difficulty::Extreme, {Entity("Reality Warpers", 150, 50), Entity("Void Dwellers", 180, 60)})
    };
}

void Game::displayBackroomsLevels() const {
    std::cout << "\n--- Livelli delle Backrooms ---\n";
    for (size_t i = 0; i < backroomsLevels.size(); ++i) {
        const auto& level = backroomsLevels[i];
        std::cout << i + 1 << ". " << level.getName() << "\n";
        std::cout << "   " << level.getDescription() << "\n";
    }
}

Entity Game::getRandomEntity() const {
    static const std::vector<Entity> entityPool = {
        Entity("Hound", 30, 10),
        Entity("Faceling", 40, 15),
        Entity("Smiler", 50, 20),
        Entity("Dullers", 20, 5),
        Entity("Clumps", 35, 12),
        Entity("Crawlers", 60, 18),
        Entity("Skin-Stealer", 70, 25),
        Entity("Deathmoths", 40, 30),
        Entity("Wretch", 80, 28),
        Entity("Facerooms", 90, 20)
    };
    
    return entityPool[rand() % entityPool.size()];
}
