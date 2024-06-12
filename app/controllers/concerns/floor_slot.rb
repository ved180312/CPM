module FloorSlot
  extend ActiveSupport::Concern

  # will show booked floor
  def booked_floor
    @floor = Floor.find(params[:id]).slots.booked
  end
    
  # will show emplty floor
  def empty_floor
    @floor = Floor.find(params[:id]).slots.empty
  end

  # will show booked slots
  def booked_slot
    @slot = Slot.all.booked
  end
  
  # will show emplty slots
  def empty_slot 
    @slot = Slot.all.empty
  end
end 