class CreateUserDetailService
  def initialize(id)
    @id = id
  end

  def call
    @slot = Slot.find(@id)
    if @slot.user_detail
    raise "Already Booked" 
    end
  end
end