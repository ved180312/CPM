module FloorSlot
    extend ActiveSupport::Concern


    # floor actions

    def booked_floor
        @floor = Floor.find(params[:id]).slots.booked
      end
      
      def empty_floor
        @floor = Floor.find(params[:id]).slots.empty
      end

    # slot actions

    def booked_slot
      @slot = Slot.all.booked
    end
    
    def empty_slot 
      @slot = Slot.all.empty
    end


end 