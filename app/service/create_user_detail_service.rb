# frozen_string_literal: true

class CreateUserDetailService
  def initialize(id)
    @id = id
  end

  def call
    @slot = Slot.find(@id)
    raise 'Already Booked' if @slot.user_detail
  end
end
