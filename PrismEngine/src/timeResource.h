#pragma once
#include <cmath>
#include <chrono>


namespace prism {
	namespace scene {
        /// @brief Стандартный ресурс для управления игровым временем
        /// @details Предоставляет как масштабируемое (игровое) время, так и реальное (немасштабируемое) время.
        /// Масштабируемое время используется для игровой логики, реальное - для системных операций.
        struct TimeResource
        {
            // === Масштабируемое время (игровое) ===
            double_t deltaTime = 0.0;      /// Изменение времени за кадр с учетом timeScale
            double_t time = 0.0;           /// Накопленное время с учетом timeScale

            // === Немасштабируемое время (реальное) ===
            double_t unscaledDeltaTime = 0.0;  /// Реальное изменение времени за кадр
            double_t unscaledTime = 0.0;       /// Реальное накопленное время

            double timeScale = 1.0;      /// Масштаб времени (1.0 = нормальная скорость)

            // === Настройки FPS Cap ===
        private:
            uint32_t targetFPS = 60;            /// Целевое количество кадров в секунду, при 0 - не ограниченно
            double_t minFrameTime = 0.0;        /// Минимальное время кадра в секундах (вычисляется автоматически)
        public:

            // === Методы управления ===

            /// @brief Обновляет временные значения
            /// @param rawDeltaTime Сырое время прошедшее с предыдущего кадра
            void update(double_t rawDeltaTime) {
                unscaledDeltaTime = rawDeltaTime;
                unscaledTime += rawDeltaTime;

                deltaTime = rawDeltaTime * timeScale;
                time += deltaTime;
            }

            /// @brief Инициализация настроек FPS
            /// @param fps Целевой FPS (0 = без лимита)
            void setFPSCap(uint32_t fps) {
                targetFPS = fps;
                minFrameTime = (targetFPS > 0) ? (1.0 / targetFPS) : 0.0;
            }

            uint32_t getFPSCap() const {
                return targetFPS;
            }

            /// @brief Проверяет, нужно ли ждать для соблюдения FPS cap
            /// @param frameStartTime Время начала текущего кадра
            /// @return Время ожидания в секундах (0 если ждать не нужно)
            double_t calculateWaitTime(std::chrono::steady_clock::time_point frameStartTime) const {
                if (!isFpsCap() || minFrameTime <= 0.0) return 0.0;

                auto now = std::chrono::steady_clock::now();
                double_t elapsed = std::chrono::duration<double_t>(now - frameStartTime).count();
                double_t waitTime = minFrameTime - elapsed;

                return (waitTime > 0.001) ? waitTime : 0.0; // порог 1мс для избежания микро-ожиданий
            }

            double_t getMinFrameTime() const {
                return minFrameTime;
            }

            /// @brief Текущий FPS для статистики
            double_t getCurrentFPS() const {
                return (unscaledDeltaTime > 0.0) ? (1.0 / unscaledDeltaTime) : 0.0;
            }

            /// @brief Время последнего кадра в мс
            double_t frameTime() const {
                return unscaledDeltaTime * 1000.0;
            }

            /// @brief Устанавливает масштаб времени
            /// @param scale Новый масштаб (1.0 = нормальная скорость)
            void setScale(double scale) {
                timeScale = scale;
            }

            /// @brief Приостанавливает время (устанавливает масштаб в 0)
            void pause() {
                timeScale = 0.0;
            }

            /// @brief Возобновляет время (устанавливает масштаб в 1.0)
            void resume() {
                timeScale = 1.0;
            }

            /// @brief Переключает паузу
            void togglePause() {
                timeScale = (timeScale == 0.0) ? 1.0 : 0.0;
            }

            /// @brief Проверяет, остановлено ли время
            /// @return true если время приостановлено (timeScale == 0)
            bool isPaused() const {
                return timeScale == 0.0;
            }

            /// @brief Сбрасывает накопленное время
            /// @param keepScale Сохранять ли текущий масштаб времени
            void reset(bool keepScale = true) {
                time = 0.0;
                unscaledTime = 0.0;
                if (!keepScale) {
                    timeScale = 1.0;
                }
            }

            /// @brief Включено ли ограничение FPS
            bool isFpsCap() const {
                return targetFPS;
            }
        };
	}
}