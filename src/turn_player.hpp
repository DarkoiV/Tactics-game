#include "turn.hpp"

class cTurnPlayer: public cTurn{
	private:

	public:
		// Destructor
		~cTurnPlayer();

		// Methods
		void start()       override;
		bool isCompleted() override;

		// Turn Loop
		void process(eBUTTON p_input) override;
		void update()                 override;
		void draw()                   override;
};
